#include "../src/cuckoofilter.h"

#include <assert.h>

#include <iostream>

using namespace cuckoofilterbio1;

std::string generateKMer(size_t k) {
  static const char bases[] = "ACGT";

  std::string k_mer;

  k_mer.reserve(k);

  for (int i = 0; i < k; ++i) k_mer += bases[rand() % (sizeof(bases) - 1)];

  return k_mer;
}

void test_max_item() {
  CuckooFilter<uint32_t> cf(10);

  while (cf.Add(generateKMer(20)) == Ok)
    ;

  assert(cf.Size() <= 10);

  std::cout << "PASS test_max_item" << std::endl;
}

void test_added_item_in_filter() {
  CuckooFilter<> cf(10);
  std::string s = generateKMer(20);

  assert(cf.Add(s) == Ok);
  assert(cf.Contain(s) == Ok);
  assert(cf.Size() == (size_t)1);

  // ne dodani nije u filteru
  assert(cf.Contain(generateKMer(20)) != Ok);

  std::cout << "PASS test_added_item_in_filter" << std::endl;
}

void test_remove_item() {
  CuckooFilter<> cf(10);

  std::string s = generateKMer(20);

  assert(cf.Add(s) == Ok);

  assert(cf.Contain(s) == Ok);

  assert(cf.Delete(s) == Ok);

  assert(cf.Contain(s) != Ok);

  std::cout << "PASS test_remove_item" << std::endl;
}

int main(int argc, const char* argv[]) {
  test_max_item();
  test_added_item_in_filter();
  test_remove_item();

  return 0;
}