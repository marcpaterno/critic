////////////////////////////////////////////////////////////////////////
// Class:       TestRemoveCachedProduct
// Module Type: analyzer
// File:        TestRemoveCachedProduct_module.cc
//
// Generated at Thu Jul 24 13:06:11 2014 by Christopher Green using artmod
// from cetpkgsupport v1_06_02.
////////////////////////////////////////////////////////////////////////

#include "boost/test/unit_test.hpp"

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "art/test/TestObjects/ToyProducts.h"
#include "fhiclcpp/fwd.h"

namespace arttest {
  class TestRemoveCachedProduct;
}

class arttest::TestRemoveCachedProduct : public art::EDAnalyzer {
public:
  explicit TestRemoveCachedProduct(fhicl::ParameterSet const& p);
  // The destructor generated by the compiler is fine for classes
  // without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  TestRemoveCachedProduct(TestRemoveCachedProduct const&) = delete;
  TestRemoveCachedProduct(TestRemoveCachedProduct&&) = delete;
  TestRemoveCachedProduct& operator=(TestRemoveCachedProduct const&) = delete;
  TestRemoveCachedProduct& operator=(TestRemoveCachedProduct&&) = delete;
  void analyze(art::Event const& e) override;

  void endSubRun(art::SubRun const& sr) override;
  void endRun(art::Run const& r) override;

private:
  // Declare member data here.
};

arttest::TestRemoveCachedProduct::TestRemoveCachedProduct(
  fhicl::ParameterSet const& p)
  : EDAnalyzer{p}
{}

void
arttest::TestRemoveCachedProduct::analyze(art::Event const& e)
{
  art::Handle<std::vector<int>> hi;
  BOOST_TEST(!hi.isValid());
  BOOST_TEST(!hi.removeProduct());
  BOOST_TEST(e.getByLabel("m1a", hi));
  BOOST_TEST(hi.isValid());
  BOOST_TEST(hi->size() == 16ul);
  BOOST_TEST(hi.removeProduct());
  BOOST_TEST(!hi.isValid());
}

void
arttest::TestRemoveCachedProduct::endSubRun(art::SubRun const& sr)
{
  art::Handle<IntProduct> hi;
  BOOST_TEST(!hi.isValid());
  BOOST_TEST(!hi.removeProduct());
  sr.getByLabel("m2", hi);
  BOOST_TEST(hi.isValid());
  BOOST_TEST(hi->value == 1);
  BOOST_TEST(hi.removeProduct());
  BOOST_TEST(!hi.isValid());
}

void
arttest::TestRemoveCachedProduct::endRun(art::Run const& r)
{
  art::Handle<IntProduct> hi;
  BOOST_TEST(!hi.isValid());
  BOOST_TEST(!hi.removeProduct());
  r.getByLabel("m3", hi);
  BOOST_TEST(hi.isValid());
  BOOST_TEST(hi->value == 2);
  BOOST_TEST(hi.removeProduct());
  BOOST_TEST(!hi.isValid());
}

DEFINE_ART_MODULE(arttest::TestRemoveCachedProduct)
