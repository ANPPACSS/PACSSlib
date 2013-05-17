//
// File generated by rootcint at Fri May 17 11:43:28 2013

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME LYSORunDict
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "LYSORunDict.h"

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
   void LYSORun_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void *new_LYSORun(void *p = 0);
   static void *newArray_LYSORun(Long_t size, void *p);
   static void delete_LYSORun(void *p);
   static void deleteArray_LYSORun(void *p);
   static void destruct_LYSORun(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LYSORun*)
   {
      ::LYSORun *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LYSORun >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LYSORun", ::LYSORun::Class_Version(), "./LYSORun.hh", 8,
                  typeid(::LYSORun), DefineBehavior(ptr, ptr),
                  &::LYSORun::Dictionary, isa_proxy, 4,
                  sizeof(::LYSORun) );
      instance.SetNew(&new_LYSORun);
      instance.SetNewArray(&newArray_LYSORun);
      instance.SetDelete(&delete_LYSORun);
      instance.SetDeleteArray(&deleteArray_LYSORun);
      instance.SetDestructor(&destruct_LYSORun);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LYSORun*)
   {
      return GenerateInitInstanceLocal((::LYSORun*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::LYSORun*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
TClass *LYSORun::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *LYSORun::Class_Name()
{
   return "LYSORun";
}

//______________________________________________________________________________
const char *LYSORun::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LYSORun*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LYSORun::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LYSORun*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void LYSORun::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LYSORun*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *LYSORun::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LYSORun*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
void LYSORun::Streamer(TBuffer &R__b)
{
   // Stream an object of class LYSORun.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LYSORun::Class(),this);
   } else {
      R__b.WriteClassBuffer(LYSORun::Class(),this);
   }
}

//______________________________________________________________________________
void LYSORun::ShowMembers(TMemberInspector &R__insp)
{
      // Inspect the data members of an object of class LYSORun.
      TClass *R__cl = ::LYSORun::IsA();
      if (R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*event", &event);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*cPlotEnergyHist", &cPlotEnergyHist);
      PACSSRun::ShowMembers(R__insp);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LYSORun(void *p) {
      return  p ? new(p) ::LYSORun : new ::LYSORun;
   }
   static void *newArray_LYSORun(Long_t nElements, void *p) {
      return p ? new(p) ::LYSORun[nElements] : new ::LYSORun[nElements];
   }
   // Wrapper around operator delete
   static void delete_LYSORun(void *p) {
      delete ((::LYSORun*)p);
   }
   static void deleteArray_LYSORun(void *p) {
      delete [] ((::LYSORun*)p);
   }
   static void destruct_LYSORun(void *p) {
      typedef ::LYSORun current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LYSORun

/********************************************************
* LYSORunDict.cc
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

extern "C" void G__cpp_reset_tagtableLYSORunDict();

extern "C" void G__set_cpp_environmentLYSORunDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("LYSORun.hh");
  G__cpp_reset_tagtableLYSORunDict();
}
#include <new>
extern "C" int G__cpp_dllrevLYSORunDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* LYSORun */
static int G__LYSORunDict_656_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   LYSORun* p = NULL;
   char* gvp = (char*) G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new LYSORun[n];
     } else {
       p = new((void*) gvp) LYSORun[n];
     }
   } else {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new LYSORun;
     } else {
       p = new((void*) gvp) LYSORun;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__LYSORunDictLN_LYSORun));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__LYSORunDict_656_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   LYSORun* p = NULL;
   char* gvp = (char*) G__getgvp();
   //m: 1
   if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
     p = new LYSORun(*((string*) G__int(libp->para[0])));
   } else {
     p = new((void*) gvp) LYSORun(*((string*) G__int(libp->para[0])));
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__LYSORunDictLN_LYSORun));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__LYSORunDict_656_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) ((LYSORun*) G__getstructoffset())->GetEvent());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__LYSORunDict_656_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) ((LYSORun*) G__getstructoffset())->GetEvent((int) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__LYSORunDict_656_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) ((LYSORun*) G__getstructoffset())->GetNextEvent());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__LYSORunDict_656_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((LYSORun*) G__getstructoffset())->PlotEnergyHist();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__LYSORunDict_656_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) LYSORun::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__LYSORunDict_656_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) LYSORun::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__LYSORunDict_656_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) LYSORun::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__LYSORunDict_656_0_10(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      LYSORun::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__LYSORunDict_656_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((LYSORun*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__LYSORunDict_656_0_15(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) LYSORun::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__LYSORunDict_656_0_16(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) LYSORun::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__LYSORunDict_656_0_17(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) LYSORun::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__LYSORunDict_656_0_18(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) LYSORun::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__LYSORunDict_656_0_19(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   LYSORun* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new LYSORun(*(LYSORun*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__LYSORunDictLN_LYSORun));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef LYSORun G__TLYSORun;
static int G__LYSORunDict_656_0_20(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
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
       delete[] (LYSORun*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((LYSORun*) (soff+(sizeof(LYSORun)*i)))->~G__TLYSORun();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (LYSORun*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((LYSORun*) (soff))->~G__TLYSORun();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__LYSORunDict_656_0_21(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   LYSORun* dest = (LYSORun*) G__getstructoffset();
   *dest = *(LYSORun*) libp->para[0].ref;
   const LYSORun& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* LYSORun */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncLYSORunDict {
 public:
  G__Sizep2memfuncLYSORunDict(): p(&G__Sizep2memfuncLYSORunDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncLYSORunDict::*p)();
};

size_t G__get_sizep2memfuncLYSORunDict()
{
  G__Sizep2memfuncLYSORunDict a;
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
extern "C" void G__cpp_setup_inheritanceLYSORunDict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__LYSORunDictLN_LYSORun))) {
     LYSORun *G__Lderived;
     G__Lderived=(LYSORun*)0x1000;
     {
       PACSSRun *G__Lpbase=(PACSSRun*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__LYSORunDictLN_LYSORun),G__get_linked_tagnum(&G__LYSORunDictLN_PACSSRun),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
     {
       TObject *G__Lpbase=(TObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__LYSORunDictLN_LYSORun),G__get_linked_tagnum(&G__LYSORunDictLN_TObject),(long)G__Lpbase-(long)G__Lderived,1,0);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableLYSORunDict() {

   /* Setting up typedef entry */
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__LYSORunDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__LYSORunDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__LYSORunDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__LYSORunDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__LYSORunDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__LYSORunDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__LYSORunDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__LYSORunDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__LYSORunDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__LYSORunDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<std::bidirectional_iterator_tag,TObject*,std::ptrdiff_t,const TObject**,const TObject*&>",117,G__get_linked_tagnum(&G__LYSORunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,std::ptrdiff_t,const TObject**,const TObject*&>",117,G__get_linked_tagnum(&G__LYSORunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*>",117,G__get_linked_tagnum(&G__LYSORunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,long>",117,G__get_linked_tagnum(&G__LYSORunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,long,const TObject**>",117,G__get_linked_tagnum(&G__LYSORunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("map<std::string,TObjArray*>",117,G__get_linked_tagnum(&G__LYSORunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("map<string,TObjArray*>",117,G__get_linked_tagnum(&G__LYSORunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("map<string,TObjArray*>",117,G__get_linked_tagnum(&G__LYSORunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("map<string,TObjArray*,less<string> >",117,G__get_linked_tagnum(&G__LYSORunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("pair<UInt_t,Int_t>",117,G__get_linked_tagnum(&G__LYSORunDictLN_pairlEunsignedsPintcOintgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<std::pair<UInt_t,Int_t> >",117,G__get_linked_tagnum(&G__LYSORunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<pair<UInt_t,Int_t> >",117,G__get_linked_tagnum(&G__LYSORunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__LYSORunDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__LYSORunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__LYSORunDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__LYSORunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<pair<unsigned int,int> >",117,G__get_linked_tagnum(&G__LYSORunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Float_t>",117,G__get_linked_tagnum(&G__LYSORunDictLN_TVectorTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Double_t>",117,G__get_linked_tagnum(&G__LYSORunDictLN_TVectorTlEdoublegR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTBase<Float_t>",117,G__get_linked_tagnum(&G__LYSORunDictLN_TMatrixTBaselEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTBase<Double_t>",117,G__get_linked_tagnum(&G__LYSORunDictLN_TMatrixTBaselEdoublegR),0,-1);
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* LYSORun */
static void G__setup_memvarLYSORun(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__LYSORunDictLN_LYSORun));
   { LYSORun *p; p=(LYSORun*)0x1000; if (p) { }
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__LYSORunDictLN_LYSOEvent),-1,-1,2,"event=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__LYSORunDictLN_TCanvas),-1,-1,2,"cPlotEnergyHist=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__LYSORunDictLN_TClass),-1,-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarLYSORunDict() {
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
static void G__setup_memfuncLYSORun(void) {
   /* LYSORun */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__LYSORunDictLN_LYSORun));
   G__memfunc_setup("LYSORun",636,G__LYSORunDict_656_0_1, 105, G__get_linked_tagnum(&G__LYSORunDictLN_LYSORun), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("LYSORun",636,G__LYSORunDict_656_0_2, 105, G__get_linked_tagnum(&G__LYSORunDictLN_LYSORun), -1, 0, 1, 1, 1, 0, "u 'string' - 0 - newFileName", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetEvent",802,G__LYSORunDict_656_0_3, 85, G__get_linked_tagnum(&G__LYSORunDictLN_LYSOEvent), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetEvent",802,G__LYSORunDict_656_0_4, 85, G__get_linked_tagnum(&G__LYSORunDictLN_LYSOEvent), -1, 0, 1, 1, 1, 0, "i - - 0 - nEvent", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetNextEvent",1217,G__LYSORunDict_656_0_5, 85, G__get_linked_tagnum(&G__LYSORunDictLN_LYSOEvent), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("PlotEnergyHist",1441,G__LYSORunDict_656_0_6, 121, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Class",502,G__LYSORunDict_656_0_7, 85, G__get_linked_tagnum(&G__LYSORunDictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (TClass* (*)())(&LYSORun::Class) ), 0);
   G__memfunc_setup("Class_Name",982,G__LYSORunDict_656_0_8, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&LYSORun::Class_Name) ), 0);
   G__memfunc_setup("Class_Version",1339,G__LYSORunDict_656_0_9, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (Version_t (*)())(&LYSORun::Class_Version) ), 0);
   G__memfunc_setup("Dictionary",1046,G__LYSORunDict_656_0_10, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&LYSORun::Dictionary) ), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__LYSORunDictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TMemberInspector' - 1 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__LYSORunDict_656_0_14, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - ClassDef_StreamerNVirtual_b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__LYSORunDict_656_0_15, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&LYSORun::DeclFileName) ), 0);
   G__memfunc_setup("ImplFileLine",1178,G__LYSORunDict_656_0_16, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&LYSORun::ImplFileLine) ), 0);
   G__memfunc_setup("ImplFileName",1171,G__LYSORunDict_656_0_17, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&LYSORun::ImplFileName) ), 0);
   G__memfunc_setup("DeclFileLine",1152,G__LYSORunDict_656_0_18, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&LYSORun::DeclFileLine) ), 0);
   // automatic copy constructor
   G__memfunc_setup("LYSORun", 636, G__LYSORunDict_656_0_19, (int) ('i'), G__get_linked_tagnum(&G__LYSORunDictLN_LYSORun), -1, 0, 1, 1, 1, 0, "u 'LYSORun' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~LYSORun", 762, G__LYSORunDict_656_0_20, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 1);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__LYSORunDict_656_0_21, (int) ('u'), G__get_linked_tagnum(&G__LYSORunDictLN_LYSORun), -1, 1, 1, 1, 1, 0, "u 'LYSORun' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncLYSORunDict() {
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
extern "C" void G__cpp_setup_globalLYSORunDict() {
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

extern "C" void G__cpp_setup_funcLYSORunDict() {
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
G__linked_taginfo G__LYSORunDictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_TObject = { "TObject" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_string = { "string" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR = { "iterator<bidirectional_iterator_tag,TObject*,long,const TObject**,const TObject*&>" , 115 , -1 };
G__linked_taginfo G__LYSORunDictLN_TCanvas = { "TCanvas" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR = { "map<string,TObjArray*,less<string>,allocator<pair<const string,TObjArray*> > >" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_pairlEunsignedsPintcOintgR = { "pair<unsigned int,int>" , 115 , -1 };
G__linked_taginfo G__LYSORunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR = { "vector<pair<unsigned int,int>,allocator<pair<unsigned int,int> > >" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<pair<unsigned int,int>,allocator<pair<unsigned int,int> > >::iterator>" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_TVectorTlEfloatgR = { "TVectorT<float>" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_TVectorTlEdoublegR = { "TVectorT<double>" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_TMatrixTBaselEfloatgR = { "TMatrixTBase<float>" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_TMatrixTBaselEdoublegR = { "TMatrixTBase<double>" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_LYSOEvent = { "LYSOEvent" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_PACSSRun = { "PACSSRun" , 99 , -1 };
G__linked_taginfo G__LYSORunDictLN_LYSORun = { "LYSORun" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableLYSORunDict() {
  G__LYSORunDictLN_TClass.tagnum = -1 ;
  G__LYSORunDictLN_TBuffer.tagnum = -1 ;
  G__LYSORunDictLN_TMemberInspector.tagnum = -1 ;
  G__LYSORunDictLN_TObject.tagnum = -1 ;
  G__LYSORunDictLN_string.tagnum = -1 ;
  G__LYSORunDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__LYSORunDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__LYSORunDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__LYSORunDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__LYSORunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR.tagnum = -1 ;
  G__LYSORunDictLN_TCanvas.tagnum = -1 ;
  G__LYSORunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR.tagnum = -1 ;
  G__LYSORunDictLN_pairlEunsignedsPintcOintgR.tagnum = -1 ;
  G__LYSORunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR.tagnum = -1 ;
  G__LYSORunDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__LYSORunDictLN_TVectorTlEfloatgR.tagnum = -1 ;
  G__LYSORunDictLN_TVectorTlEdoublegR.tagnum = -1 ;
  G__LYSORunDictLN_TMatrixTBaselEfloatgR.tagnum = -1 ;
  G__LYSORunDictLN_TMatrixTBaselEdoublegR.tagnum = -1 ;
  G__LYSORunDictLN_LYSOEvent.tagnum = -1 ;
  G__LYSORunDictLN_PACSSRun.tagnum = -1 ;
  G__LYSORunDictLN_LYSORun.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableLYSORunDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_TClass);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_TObject);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_string);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_TCanvas);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_pairlEunsignedsPintcOintgR);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_TVectorTlEfloatgR);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_TVectorTlEdoublegR);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_TMatrixTBaselEfloatgR);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_TMatrixTBaselEdoublegR);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_LYSOEvent);
   G__get_linked_tagnum_fwd(&G__LYSORunDictLN_PACSSRun);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__LYSORunDictLN_LYSORun),sizeof(LYSORun),-1,324864,(char*)NULL,G__setup_memvarLYSORun,G__setup_memfuncLYSORun);
}
extern "C" void G__cpp_setupLYSORunDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupLYSORunDict()");
  G__set_cpp_environmentLYSORunDict();
  G__cpp_setup_tagtableLYSORunDict();

  G__cpp_setup_inheritanceLYSORunDict();

  G__cpp_setup_typetableLYSORunDict();

  G__cpp_setup_memvarLYSORunDict();

  G__cpp_setup_memfuncLYSORunDict();
  G__cpp_setup_globalLYSORunDict();
  G__cpp_setup_funcLYSORunDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncLYSORunDict();
  return;
}
class G__cpp_setup_initLYSORunDict {
  public:
    G__cpp_setup_initLYSORunDict() { G__add_setup_func("LYSORunDict",(G__incsetup)(&G__cpp_setupLYSORunDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initLYSORunDict() { G__remove_setup_func("LYSORunDict"); }
};
G__cpp_setup_initLYSORunDict G__cpp_setup_initializerLYSORunDict;

