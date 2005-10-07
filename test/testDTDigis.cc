/**
   \file
   Test suit for DTDigis

   \author Stefano ARGIRO
   \version $Id: testDTDigis.cc,v 1.3 2005/08/23 09:10:45 argiro Exp $
   \date 29 Jun 2005

   \note This test is not exaustive     
*/

static const char CVSId[] = "$Id: testDTDigis.cc,v 1.3 2005/08/23 09:10:45 argiro Exp $";

#include <cppunit/extensions/HelperMacros.h>
#include <DataFormats/DTDigi/interface/DTDigi.h>
#include <DataFormats/DTDigi/interface/DTDigiCollection.h>
#include <DataFormats/MuonDetId/interface/DTDetId.h>


class testDTDigis: public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(testDTDigis);

  CPPUNIT_TEST(testDigiPacking);
  CPPUNIT_TEST(testDigiCollectionInsert);
  CPPUNIT_TEST(testDigiCollectionPut);

  CPPUNIT_TEST_SUITE_END();

public:


  void setUp(){}
  void tearDown(){}  
  void testDigiPacking();
  void testDigiCollectionInsert();
  void testDigiCollectionPut();
}; 

///registration of the test so that the runner can find it
CPPUNIT_TEST_SUITE_REGISTRATION(testDTDigis);


void testDTDigis::testDigiPacking(){
  CPPUNIT_ASSERT (sizeof(DTDigi::PersistentPacking)==sizeof(DTDigi::PackedDigiType));
  CPPUNIT_ASSERT(sizeof(DTDigi::ChannelPacking)==sizeof(int));
}


void testDTDigis::testDigiCollectionPut(){

  DTDetId layer(2,7,8,1,244);

  DTDigiCollection digiCollection;

  std::vector<DTDigi> digivec;
  for (int i=0; i<10; ++i){
    DTDigi::PackedDigiType pd;
    pd.wire=1+i;
    pd.counts=5+i;

    DTDigi digi(pd);
    digivec.push_back(digi);
  }

  digiCollection.put(std::make_pair(digivec.begin(), digivec.end()),layer);
    
  DTDigiCollection::DigiRangeIterator detUnitIt;
  for (detUnitIt=digiCollection.begin();
       detUnitIt!=digiCollection.end();
       ++detUnitIt){

    int i=0;
    for (DTDigiCollection::const_iterator digiIt = 
	  detUnitIt->second.first;
	  digiIt!=detUnitIt->second.second;
	 ++digiIt){

      

      CPPUNIT_ASSERT((*digiIt).wire()==1+i);
      CPPUNIT_ASSERT((*digiIt).countsTDC()==5+i);
      i++;
      
    }// for digis in layer
   }// for layers

}

void testDTDigis::testDigiCollectionInsert(){

  DTDigi::PackedDigiType pd;
  pd.wire=1;
  pd.number=4;
  pd.counts=5;

  DTDigi digi(pd);


  DTDetId layer(2,7,8,1,244);

  DTDigiCollection digiCollection;

  digiCollection.insertDigi(layer,digi);

  //  DTDigiCollection::DetUnitIds layers = digiCollection.layers();

//   for (DTDigiCollection::DetUnitIds::const_iterator layerIt = layers.begin();
//        layerIt!= layers.end(); ++layerIt){

  DTDigiCollection::DigiRangeIterator detUnitIt;
  for (detUnitIt=digiCollection.begin();
       detUnitIt!=digiCollection.end();
       ++detUnitIt){

    for (DTDigiCollection::const_iterator digiIt =
          detUnitIt->second.first;
          digiIt!=detUnitIt->second.second;
         ++digiIt){


      CPPUNIT_ASSERT((*digiIt).wire()==1);
      CPPUNIT_ASSERT((*digiIt).number()==4);
      CPPUNIT_ASSERT((*digiIt).countsTDC()==5);


    }// for digis in layer
   }// for layers

}
