#include <string.h>
#include <stdlib.h>
#include "putils/pdict.h"
#include "unity.h"

#define DICT_DATA_LEN 10
#define KEYS_LEN 10

pdict *D = 0;
size_t *data = 0;
char (*keys)[KEYS_LEN];

void setUp(void) {
    D = pdict_create();
}

void tearDown(void) {
    pdict_destroy(D);
}

void loadDict(void) {
    keys = malloc(sizeof(char[DICT_DATA_LEN][KEYS_LEN]));
    data = calloc(1, DICT_DATA_LEN*sizeof(size_t));
    for( size_t i = 0; i < DICT_DATA_LEN; ++i) {
        snprintf(keys[i], KEYS_LEN, "%c", (int) i + 65);
        data[i] = i + 1;
        pdict_put(D, keys[i], &data[i]);
    }
}

void test_create_NewDictShouldBeEmpty(void) {
    TEST_ASSERT_TRUE(pdict_is_empty(D));
}

void test_create_NewDictShouldNotBeNull(void) {
    TEST_ASSERT_NOT_NULL(D);
}

void test_size_ShouldBeZeroForANewDict(void) {
    TEST_ASSERT_EQUAL_UINT(pdict_size(D), 0);
}

void test_isEmpty_ShouldReturnTrueOnAnEmptyDict(void) {
    TEST_ASSERT_TRUE(pdict_is_empty(D));
}

void test_size_SizeOfNewDictWithOneItemShouldBeOne(void) {
    char *key = malloc(sizeof(char[1][KEYS_LEN]));
    data = calloc(1, sizeof(size_t));
    data[0] = 0;
    snprintf(key, KEYS_LEN, "%s", "0_key");
    pdict_put(D, key, &data[0]);
    TEST_ASSERT_EQUAL_UINT(pdict_size(D), 1);
}

void test_size_ShouldBeEqualToTheNumberOfAddedElements(void) {
    loadDict();
    TEST_ASSERT_EQUAL_UINT(pdict_size(D), DICT_DATA_LEN);
}

void test_size_ShouldBeZeroForACleanDict(void) {
    loadDict();
    pdict_clean(D);
    TEST_ASSERT_EQUAL_UINT(pdict_size(D), 0);
}

void test_size_ShouldNotBeZeroAfterAddingElements(void) {
    loadDict();
    TEST_ASSERT_TRUE(pdict_size(D) != 0);
}

void test_add_ShouldAddANewElement(void) {
    char *key = malloc(sizeof(char[1][KEYS_LEN]));
    data = calloc(1, sizeof(size_t));
    snprintf(key, KEYS_LEN, "%s", "99_key");
    data[0] = 99;
    TEST_ASSERT_TRUE(pdict_is_empty(D));
    pdict_put(D, key, &data[0]);
    TEST_ASSERT_EQUAL_UINT(1, pdict_size(D));
}

void test_append_ShouldAddAnElementToAnEmptyDict(void) {
    char* key = malloc(sizeof(char[1][KEYS_LEN]));
    data = calloc(1, sizeof(size_t));
    snprintf(key, KEYS_LEN, "%s", "1_key");
    data[0] = 1;
    TEST_ASSERT_TRUE(pdict_is_empty(D));
    pdict_put(D, key, &data[0]);
    TEST_ASSERT_FALSE(pdict_is_empty(D));
}

void test_isEmpty_ShouldReturnFalseOnALoadedDict(void) {
    loadDict();
    TEST_ASSERT_FALSE(pdict_is_empty(D));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_create_NewDictShouldBeEmpty);
    RUN_TEST(test_create_NewDictShouldNotBeNull);

    RUN_TEST(test_size_ShouldBeZeroForANewDict);
    RUN_TEST(test_size_ShouldBeEqualToTheNumberOfAddedElements);
    RUN_TEST(test_size_SizeOfNewDictWithOneItemShouldBeOne);
    RUN_TEST(test_size_ShouldBeZeroForACleanDict);
    RUN_TEST(test_size_ShouldNotBeZeroAfterAddingElements);

    RUN_TEST(test_isEmpty_ShouldReturnTrueOnAnEmptyDict);
    RUN_TEST(test_isEmpty_ShouldReturnFalseOnALoadedDict);

    RUN_TEST(test_add_ShouldAddANewElement);

    RUN_TEST(test_append_ShouldAddAnElementToAnEmptyDict);

    return UNITY_END();
}

/* Pending

test_plist based:
void test_get_ShouldGetAValidElementFromTheDict(){};
void_test_get_ShouldGetAllElementsFromTheDict(){};
void test_remove_ShouldRemoveAnElementFromDict(void) {}
void test_remove_ShouldRemoveFirstElementFromDict(void) {}
void test_remove_ShouldRemoveLastElementFromList(void) {}
void test_removeDestroy_ShouldRemoveAndDestroyAnElement(void) {}
*/
