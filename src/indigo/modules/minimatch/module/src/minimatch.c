/****************************************************************
 *
 *        Copyright 2014, Big Switch Networks, Inc.
 *
 * Licensed under the Eclipse Public License, Version 1.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *        http://www.eclipse.org/legal/epl-v10.html
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the
 * License.
 *
 ****************************************************************/

#include <minimatch/minimatch.h>
#include <AIM/aim.h>
#include <murmur/murmur.h>

void
minimatch_init(minimatch_t *minimatch, const of_match_t *match)
{
    int i, j;
    int num_words = 0;
    int idx = 0;
    uint32_t *fields = (uint32_t *)&match->fields;
    uint32_t *masks = (uint32_t *)&match->masks;

    minimatch->version = match->version;
    memset(minimatch->bitmap, 0, sizeof(minimatch->bitmap));

    /*
     * Find the nonzero match words and set their bit in the bitmap.
     */
    for (i = 0; i < OF_MATCH_FIELDS_WORDS; i++) {
        if (masks[i]) {
            num_words += 2;
            minimatch->bitmap[i/32] |= (1 << (i % 32));
        }
    }

    minimatch->num_words = num_words;
    minimatch->words = aim_malloc(sizeof(uint32_t) * num_words);

    /*
     * For each bit set in the bitmap, copy the corresponding words from the
     * fields and masks to our words array.
     */
    for (i = 0; i < AIM_ARRAYSIZE(minimatch->bitmap); i++) {
        uint32_t bitmap_word = minimatch->bitmap[i];
        j = i * 32;

        while (bitmap_word) {
            int skip = __builtin_ctz(bitmap_word);
            bitmap_word >>= skip;
            j += skip;

            minimatch->words[idx++] = fields[j];
            minimatch->words[idx++] = masks[j];

            j++;
            bitmap_word >>= 1;
        }
    }
}

void
minimatch_cleanup(minimatch_t *minimatch)
{
    aim_free(minimatch->words);
}

void
minimatch_expand(const minimatch_t *minimatch, of_match_t *match)
{
    int i, j;
    int idx = 0;
    uint32_t *fields = (uint32_t *)&match->fields;
    uint32_t *masks = (uint32_t *)&match->masks;

    memset(match, 0, sizeof(*match));
    match->version = minimatch->version;

    /*
     * For each bit set in the bitmap, copy the corresponding words from the
     * words array to the match fields and masks.
     */
    for (i = 0; i < AIM_ARRAYSIZE(minimatch->bitmap); i++) {
        uint32_t bitmap_word = minimatch->bitmap[i];
        j = i * 32;

        while (bitmap_word) {
            int skip = __builtin_ctz(bitmap_word);
            bitmap_word >>= skip;
            j += skip;

            fields[j] = minimatch->words[idx++];
            masks[j] = minimatch->words[idx++];

            j++;
            bitmap_word >>= 1;
        }
    }
}

bool
minimatch_equal(const minimatch_t *a, const minimatch_t *b)
{
    if (memcmp(a->bitmap, b->bitmap, sizeof(a->bitmap))) {
        return false;
    }

    AIM_ASSERT(a->num_words == b->num_words, "length mismatch");

    if (memcmp(a->words, b->words, a->num_words*sizeof(uint32_t))) {
        return false;
    }

    if (a->version != b->version) {
        return false;
    }

    return true;
}

bool
minimatch_more_specific(const minimatch_t *a, const minimatch_t *b)
{
    int idx_a = 0, idx_b = 0;
    int i;

    if (b->num_words == 0) {
        /* B's mask is all zero, so A must be more specific */
        return true;
    }

    /*
     * For each match word, check that a's mask is at least as specific as b's
     * mask and that a and b agree on the fields where b's mask is set.
     */
    for (i = 0; i < AIM_ARRAYSIZE(a->bitmap); i++) {
        uint32_t bitmap_word_a = a->bitmap[i];
        uint32_t bitmap_word_b = b->bitmap[i];

        while (bitmap_word_a | bitmap_word_b) {
            int skip = __builtin_ctz(bitmap_word_a | bitmap_word_b);
            bitmap_word_a >>= skip;
            bitmap_word_b >>= skip;

            uint32_t field_a, mask_a, field_b, mask_b;

            if (bitmap_word_a & 1) {
                field_a = a->words[idx_a++];
                mask_a = a->words[idx_a++];
            } else {
                field_a = 0;
                mask_a = 0;
            }

            if (bitmap_word_b & 1) {
                field_b = b->words[idx_b++];
                mask_b = b->words[idx_b++];
            } else {
                field_b = 0;
                mask_b = 0;
            }

            if (mask_b & ~mask_a) {
                return false;
            }

            if ((field_a & mask_b) != (field_b & mask_b)) {
                return false;
            }

            bitmap_word_a >>= 1;
            bitmap_word_b >>= 1;
        }
    }

    return true;
}

bool
minimatch_overlap(const minimatch_t *a, const minimatch_t *b)
{
    int idx_a = 0, idx_b = 0;
    int i;

    /*
     * For each match word, check that a and b agree on the fields where
     * the intersection of the masks is set.
     */
    for (i = 0; i < OF_MATCH_FIELDS_WORDS; i++) {
        uint32_t field_a, mask_a, field_b, mask_b;

        if ((a->bitmap[i/32] >> (i % 32)) & 1) {
            field_a = a->words[idx_a++];
            mask_a = a->words[idx_a++];
        } else {
            field_a = 0;
            mask_a = 0;
        }

        if ((b->bitmap[i/32] >> (i % 32)) & 1) {
            field_b = b->words[idx_b++];
            mask_b = b->words[idx_b++];
        } else {
            field_b = 0;
            mask_b = 0;
        }

        if ((field_a & mask_b) != (field_b & mask_a)) {
            return false;
        }
    }

    return true;
}

uint32_t
minimatch_hash(const minimatch_t *minimatch, uint32_t seed)
{
    uint32_t h = seed;
    h = murmur_hash(&minimatch->bitmap, sizeof(minimatch->bitmap), h);
    h = murmur_hash(minimatch->words, minimatch->num_words * sizeof(uint32_t), h);
    return h;
}

void
minimatch_move(minimatch_t *dst, minimatch_t *src)
{
    *dst = *src;
    memset(src, 0, sizeof(*src));
}
