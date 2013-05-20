//
// File generated by rootcint at Mon May 20 12:27:46 2013

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME PACSSRunDict
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "PACSSRunDict.h"

#include "TClass.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"

// START OF SHADOWS

namespace ROOT {
   namespace Shadow {
   } // of namespace Shadow
} // of namespace ROOT
// END OF SHADOWS

namespace ROOT {
   void PACSSRun_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void *new_PACSSRun(void *p = 0);
   static void *newArray_PACSSRun(Long_t size, void *p);
   static void delete_PACSSRun(void *p);
   static void deleteArray_PACSSRun(void *p);
   static void destruct_PACSSRun(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PACSSRun*)
   {
      ::PACSSRun *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PACSSRun >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PACSSRun", ::PACSSRun::Class_Version(), "./PACSSRun.hh", 7,
                  typeid(::PACSSRun), DefineBehavior(ptr, ptr),
                  &::PACSSRun::Dictionary, isa_proxy, 4,
                  sizeof(::PACSSRun) );
      instance.SetNew(&new_PACSSRun);
      instance.SetNewArray(&newArray_PACSSRun);
      instance.SetDelete(&delete_PACSSRun);
      instance.SetDeleteArray(&deleteArray_PACSSRun);
      instance.SetDestructor(&destruct_PACSSRun);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PACSSRun*)
   {
      return GenerateInitInstanceLocal((::PACSSRun*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PACSSRun*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
TClass *PACSSRun::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *PACSSRun::Class_Name()
{
   return "PACSSRun";
}

//______________________________________________________________________________
const char *PACSSRun::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PACSSRun*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PACSSRun::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PACSSRun*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void PACSSRun::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PACSSRun*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *PACSSRun::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PACSSRun*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
void PACSSRun::Streamer(TBuffer &R__b)
{
   // Stream an object of class PACSSRun.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PACSSRun::Class(),this);
   } else {
      R__b.WriteClassBuffer(PACSSRun::Class(),this);
   }
}

//______________________________________________________________________________
void PACSSRun::ShowMembers(TMemberInspector &R__insp)
{
      // Inspect the data members of an object of class PACSSRun.
      TClass *R__cl = ::PACSSRun::IsA();
      if (R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__insp.GetParent(), "fileName", (void*)&fileName);
      R__insp.InspectMember("string", (void*)&fileName, "fileName.", false);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "cPrefix", (void*)&cPrefix);
      R__insp.InspectMember("string", (void*)&cPrefix, "cPrefix.", false);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*rootFile", &rootFile);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*eventTree", &eventTree);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "reportFreq", &reportFreq);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "iEvent", &iEvent);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "numEvents", &numEvents);
      TObject::ShowMembers(R__insp);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PACSSRun(void *p) {
      return  p ? new(p) ::PACSSRun : new ::PACSSRun;
   }
   static void *newArray_PACSSRun(Long_t nElements, void *p) {
      return p ? new(p) ::PACSSRun[nElements] : new ::PACSSRun[nElements];
   }
   // Wrapper around operator delete
   static void delete_PACSSRun(void *p) {
      delete ((::PACSSRun*)p);
   }
   static void deleteArray_PACSSRun(void *p) {
      delete [] ((::PACSSRun*)p);
   }
   static void destruct_PACSSRun(void *p) {
      typedef ::PACSSRun current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PACSSRun

/********************************************************
* PACSSRunDict.cc
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************/

#ifdef G__MEMTEST
#undef malloc
#undef free
#endif

#if defined(__GNUC__) && __GNUC__ >= 4 && ((__GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ >= 1) || (__GNUC_MINOR__ >= 3))
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

extern "C" void G__cpp_reset_tagtablePACSSRunDict();

extern "C" void G__set_cpp_environmentPACSSRunDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("PACSSRun.hh");
  G__cpp_reset_tagtablePACSSRunDict();
}
#include <new>
extern "C" int G__cpp_dllrevPACSSRunDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* PACSSRun */
static int G__PACSSRunDict_654_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   PACSSRun* p = NULL;
   char* gvp = (char*) G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new PACSSRun[n];
     } else {
       p = new((void*) gvp) PACSSRun[n];
     }
   } else {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new PACSSRun;
     } else {
       p = new((void*) gvp) PACSSRun;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__PACSSRunDictLN_PACSSRun));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__PACSSRunDict_654_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   PACSSRun* p = NULL;
   char* gvp = (char*) G__getgvp();
   //m: 1
   if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
     p = new PACSSRun(*((string*) G__int(libp->para[0])));
   } else {
     p = new((void*) gvp) PACSSRun(*((string*) G__int(libp->para[0])));
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__PACSSRunDictLN_PACSSRun));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__PACSSRunDict_654_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((PACSSRun*) G__getstructoffset())->GetReportFreq());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__PACSSRunDict_654_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((PACSSRun*) G__getstructoffset())->GetNumEvents());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__PACSSRunDict_654_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((PACSSRun*) G__getstructoffset())->SetReportFreq((int) G__int(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__PACSSRunDict_654_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) PACSSRun::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__PACSSRunDict_654_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) PACSSRun::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__PACSSRunDict_654_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) PACSSRun::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__PACSSRunDict_654_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      PACSSRun::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__PACSSRunDict_654_0_13(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((PACSSRun*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__PACSSRunDict_654_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) PACSSRun::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__PACSSRunDict_654_0_15(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) PACSSRun::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__PACSSRunDict_654_0_16(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) PACSSRun::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__PACSSRunDict_654_0_17(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) PACSSRun::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__PACSSRunDict_654_0_18(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   PACSSRun* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new PACSSRun(*(PACSSRun*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__PACSSRunDictLN_PACSSRun));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef PACSSRun G__TPACSSRun;
static int G__PACSSRunDict_654_0_19(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   char* gvp = (char*) G__getgvp();
   long soff = G__getstructoffset();
   int n = G__getaryconstruct();
   //
   //has_a_delete: 1
   //has_own_delete1arg: 0
   //has_own_delete2arg: 0
   //
   if (!soff) {
     return(1);
   }
   if (n) {
     if (gvp == (char*)G__PVOID) {
       delete[] (PACSSRun*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((PACSSRun*) (soff+(sizeof(PACSSRun)*i)))->~G__TPACSSRun();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (PACSSRun*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((PACSSRun*) (soff))->~G__TPACSSRun();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__PACSSRunDict_654_0_20(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   PACSSRun* dest = (PACSSRun*) G__getstructoffset();
   *dest = *(PACSSRun*) libp->para[0].ref;
   const PACSSRun& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* PACSSRun */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncPACSSRunDict {
 public:
  G__Sizep2memfuncPACSSRunDict(): p(&G__Sizep2memfuncPACSSRunDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncPACSSRunDict::*p)();
};

size_t G__get_sizep2memfuncPACSSRunDict()
{
  G__Sizep2memfuncPACSSRunDict a;
  G__setsizep2memfunc((int)a.sizep2memfunc());
  return((size_t)a.sizep2memfunc());
}


/*********************************************************
* virtual base class offset calculation interface
*********************************************************/

   /* Setting up class inheritance */

/*********************************************************
* Inheritance information setup/
*********************************************************/
extern "C" void G__cpp_setup_inheritancePACSSRunDict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__PACSSRunDictLN_PACSSRun))) {
     PACSSRun *G__Lderived;
     G__Lderived=(PACSSRun*)0x1000;
     {
       TObject *G__Lpbase=(TObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__PACSSRunDictLN_PACSSRun),G__get_linked_tagnum(&G__PACSSRunDictLN_TObject),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetablePACSSRunDict() {

   /* Setting up typedef entry */
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__PACSSRunDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__PACSSRunDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__PACSSRunDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__PACSSRunDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<std::bidirectional_iterator_tag,TObject*,std::ptrdiff_t,const TObject**,const TObject*&>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,std::ptrdiff_t,const TObject**,const TObject*&>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,long>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,long,const TObject**>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("map<std::string,TObjArray*>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("map<string,TObjArray*>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("map<string,TObjArray*>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("map<string,TObjArray*,less<string> >",117,G__get_linked_tagnum(&G__PACSSRunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("pair<UInt_t,Int_t>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_pairlEunsignedsPintcOintgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<std::pair<UInt_t,Int_t> >",117,G__get_linked_tagnum(&G__PACSSRunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<pair<UInt_t,Int_t> >",117,G__get_linked_tagnum(&G__PACSSRunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__PACSSRunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__PACSSRunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<pair<unsigned int,int> >",117,G__get_linked_tagnum(&G__PACSSRunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Float_t>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_TVectorTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Double_t>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_TVectorTlEdoublegR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTBase<Float_t>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_TMatrixTBaselEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTBase<Double_t>",117,G__get_linked_tagnum(&G__PACSSRunDictLN_TMatrixTBaselEdoublegR),0,-1);
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* PACSSRun */
static void G__setup_memvarPACSSRun(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__PACSSRunDictLN_PACSSRun));
   { PACSSRun *p; p=(PACSSRun*)0x1000; if (p) { }
   G__memvar_setup((void*)0,117,0,0,G__get_linked_tagnum(&G__PACSSRunDictLN_string),-1,-1,2,"fileName=",0,(char*)NULL);
   G__memvar_setup((void*)0,117,0,0,G__get_linked_tagnum(&G__PACSSRunDictLN_string),-1,-1,2,"cPrefix=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__PACSSRunDictLN_TFile),-1,-1,2,"rootFile=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__PACSSRunDictLN_TTree),-1,-1,2,"eventTree=",0,(char*)NULL);
   G__memvar_setup((void*)0,105,0,0,-1,-1,-1,2,"reportFreq=",0,(char*)NULL);
   G__memvar_setup((void*)0,105,0,0,-1,-1,-1,2,"iEvent=",0,(char*)NULL);
   G__memvar_setup((void*)0,105,0,0,-1,-1,-1,2,"numEvents=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__PACSSRunDictLN_TClass),-1,-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarPACSSRunDict() {
}
/***********************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
***********************************************************/

/*********************************************************
* Member function information setup for each class
*********************************************************/
static void G__setup_memfuncPACSSRun(void) {
   /* PACSSRun */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__PACSSRunDictLN_PACSSRun));
   G__memfunc_setup("PACSSRun",687,G__PACSSRunDict_654_0_1, 105, G__get_linked_tagnum(&G__PACSSRunDictLN_PACSSRun), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("PACSSRun",687,G__PACSSRunDict_654_0_2, 105, G__get_linked_tagnum(&G__PACSSRunDictLN_PACSSRun), -1, 0, 1, 1, 1, 0, "u 'string' - 0 - newFileName", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetReportFreq",1322,G__PACSSRunDict_654_0_3, 105, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetNumEvents",1221,G__PACSSRunDict_654_0_4, 105, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("SetReportFreq",1334,G__PACSSRunDict_654_0_5, 121, -1, -1, 0, 1, 1, 1, 0, "i - - 0 - newReportFreq", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Class",502,G__PACSSRunDict_654_0_6, 85, G__get_linked_tagnum(&G__PACSSRunDictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (TClass* (*)())(&PACSSRun::Class) ), 0);
   G__memfunc_setup("Class_Name",982,G__PACSSRunDict_654_0_7, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&PACSSRun::Class_Name) ), 0);
   G__memfunc_setup("Class_Version",1339,G__PACSSRunDict_654_0_8, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (Version_t (*)())(&PACSSRun::Class_Version) ), 0);
   G__memfunc_setup("Dictionary",1046,G__PACSSRunDict_654_0_9, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&PACSSRun::Dictionary) ), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__PACSSRunDictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TMemberInspector' - 1 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__PACSSRunDict_654_0_13, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - ClassDef_StreamerNVirtual_b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__PACSSRunDict_654_0_14, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&PACSSRun::DeclFileName) ), 0);
   G__memfunc_setup("ImplFileLine",1178,G__PACSSRunDict_654_0_15, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&PACSSRun::ImplFileLine) ), 0);
   G__memfunc_setup("ImplFileName",1171,G__PACSSRunDict_654_0_16, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&PACSSRun::ImplFileName) ), 0);
   G__memfunc_setup("DeclFileLine",1152,G__PACSSRunDict_654_0_17, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&PACSSRun::DeclFileLine) ), 0);
   // automatic copy constructor
   G__memfunc_setup("PACSSRun", 687, G__PACSSRunDict_654_0_18, (int) ('i'), G__get_linked_tagnum(&G__PACSSRunDictLN_PACSSRun), -1, 0, 1, 1, 1, 0, "u 'PACSSRun' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~PACSSRun", 813, G__PACSSRunDict_654_0_19, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 1);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__PACSSRunDict_654_0_20, (int) ('u'), G__get_linked_tagnum(&G__PACSSRunDictLN_PACSSRun), -1, 1, 1, 1, 1, 0, "u 'PACSSRun' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncPACSSRunDict() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
static void G__cpp_setup_global0() {

   /* Setting up global variables */
   G__resetplocal();

}

static void G__cpp_setup_global1() {
}

static void G__cpp_setup_global2() {
}

static void G__cpp_setup_global3() {
}

static void G__cpp_setup_global4() {
}

static void G__cpp_setup_global5() {
}

static void G__cpp_setup_global6() {
}

static void G__cpp_setup_global7() {

   G__resetglobalenv();
}
extern "C" void G__cpp_setup_globalPACSSRunDict() {
  G__cpp_setup_global0();
  G__cpp_setup_global1();
  G__cpp_setup_global2();
  G__cpp_setup_global3();
  G__cpp_setup_global4();
  G__cpp_setup_global5();
  G__cpp_setup_global6();
  G__cpp_setup_global7();
}

/*********************************************************
* Global function information setup for each class
*********************************************************/
static void G__cpp_setup_func0() {
   G__lastifuncposition();

}

static void G__cpp_setup_func1() {
}

static void G__cpp_setup_func2() {
}

static void G__cpp_setup_func3() {
}

static void G__cpp_setup_func4() {
}

static void G__cpp_setup_func5() {
}

static void G__cpp_setup_func6() {
}

static void G__cpp_setup_func7() {
}

static void G__cpp_setup_func8() {
}

static void G__cpp_setup_func9() {
}

static void G__cpp_setup_func10() {
}

static void G__cpp_setup_func11() {
}

static void G__cpp_setup_func12() {
}

static void G__cpp_setup_func13() {
}

static void G__cpp_setup_func14() {
}

static void G__cpp_setup_func15() {
}

static void G__cpp_setup_func16() {
}

static void G__cpp_setup_func17() {
}

static void G__cpp_setup_func18() {
}

static void G__cpp_setup_func19() {

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcPACSSRunDict() {
  G__cpp_setup_func0();
  G__cpp_setup_func1();
  G__cpp_setup_func2();
  G__cpp_setup_func3();
  G__cpp_setup_func4();
  G__cpp_setup_func5();
  G__cpp_setup_func6();
  G__cpp_setup_func7();
  G__cpp_setup_func8();
  G__cpp_setup_func9();
  G__cpp_setup_func10();
  G__cpp_setup_func11();
  G__cpp_setup_func12();
  G__cpp_setup_func13();
  G__cpp_setup_func14();
  G__cpp_setup_func15();
  G__cpp_setup_func16();
  G__cpp_setup_func17();
  G__cpp_setup_func18();
  G__cpp_setup_func19();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__PACSSRunDictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__PACSSRunDictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__PACSSRunDictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__PACSSRunDictLN_TObject = { "TObject" , 99 , -1 };
G__linked_taginfo G__PACSSRunDictLN_string = { "string" , 99 , -1 };
G__linked_taginfo G__PACSSRunDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__PACSSRunDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__PACSSRunDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__PACSSRunDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__PACSSRunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR = { "iterator<bidirectional_iterator_tag,TObject*,long,const TObject**,const TObject*&>" , 115 , -1 };
G__linked_taginfo G__PACSSRunDictLN_TFile = { "TFile" , 99 , -1 };
G__linked_taginfo G__PACSSRunDictLN_TTree = { "TTree" , 99 , -1 };
G__linked_taginfo G__PACSSRunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR = { "map<string,TObjArray*,less<string>,allocator<pair<const string,TObjArray*> > >" , 99 , -1 };
G__linked_taginfo G__PACSSRunDictLN_pairlEunsignedsPintcOintgR = { "pair<unsigned int,int>" , 115 , -1 };
G__linked_taginfo G__PACSSRunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR = { "vector<pair<unsigned int,int>,allocator<pair<unsigned int,int> > >" , 99 , -1 };
G__linked_taginfo G__PACSSRunDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<pair<unsigned int,int>,allocator<pair<unsigned int,int> > >::iterator>" , 99 , -1 };
G__linked_taginfo G__PACSSRunDictLN_TVectorTlEfloatgR = { "TVectorT<float>" , 99 , -1 };
G__linked_taginfo G__PACSSRunDictLN_TVectorTlEdoublegR = { "TVectorT<double>" , 99 , -1 };
G__linked_taginfo G__PACSSRunDictLN_TMatrixTBaselEfloatgR = { "TMatrixTBase<float>" , 99 , -1 };
G__linked_taginfo G__PACSSRunDictLN_TMatrixTBaselEdoublegR = { "TMatrixTBase<double>" , 99 , -1 };
G__linked_taginfo G__PACSSRunDictLN_PACSSRun = { "PACSSRun" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtablePACSSRunDict() {
  G__PACSSRunDictLN_TClass.tagnum = -1 ;
  G__PACSSRunDictLN_TBuffer.tagnum = -1 ;
  G__PACSSRunDictLN_TMemberInspector.tagnum = -1 ;
  G__PACSSRunDictLN_TObject.tagnum = -1 ;
  G__PACSSRunDictLN_string.tagnum = -1 ;
  G__PACSSRunDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__PACSSRunDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__PACSSRunDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__PACSSRunDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__PACSSRunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR.tagnum = -1 ;
  G__PACSSRunDictLN_TFile.tagnum = -1 ;
  G__PACSSRunDictLN_TTree.tagnum = -1 ;
  G__PACSSRunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR.tagnum = -1 ;
  G__PACSSRunDictLN_pairlEunsignedsPintcOintgR.tagnum = -1 ;
  G__PACSSRunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR.tagnum = -1 ;
  G__PACSSRunDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__PACSSRunDictLN_TVectorTlEfloatgR.tagnum = -1 ;
  G__PACSSRunDictLN_TVectorTlEdoublegR.tagnum = -1 ;
  G__PACSSRunDictLN_TMatrixTBaselEfloatgR.tagnum = -1 ;
  G__PACSSRunDictLN_TMatrixTBaselEdoublegR.tagnum = -1 ;
  G__PACSSRunDictLN_PACSSRun.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtablePACSSRunDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_TClass);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_TObject);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_string);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_TFile);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_TTree);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_pairlEunsignedsPintcOintgR);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_TVectorTlEfloatgR);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_TVectorTlEdoublegR);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_TMatrixTBaselEfloatgR);
   G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_TMatrixTBaselEdoublegR);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__PACSSRunDictLN_PACSSRun),sizeof(PACSSRun),-1,324864,(char*)NULL,G__setup_memvarPACSSRun,G__setup_memfuncPACSSRun);
}
extern "C" void G__cpp_setupPACSSRunDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupPACSSRunDict()");
  G__set_cpp_environmentPACSSRunDict();
  G__cpp_setup_tagtablePACSSRunDict();

  G__cpp_setup_inheritancePACSSRunDict();

  G__cpp_setup_typetablePACSSRunDict();

  G__cpp_setup_memvarPACSSRunDict();

  G__cpp_setup_memfuncPACSSRunDict();
  G__cpp_setup_globalPACSSRunDict();
  G__cpp_setup_funcPACSSRunDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncPACSSRunDict();
  return;
}
class G__cpp_setup_initPACSSRunDict {
  public:
    G__cpp_setup_initPACSSRunDict() { G__add_setup_func("PACSSRunDict",(G__incsetup)(&G__cpp_setupPACSSRunDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initPACSSRunDict() { G__remove_setup_func("PACSSRunDict"); }
};
G__cpp_setup_initPACSSRunDict G__cpp_setup_initializerPACSSRunDict;

