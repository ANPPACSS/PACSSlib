//
// File generated by rootcint at Mon May 20 12:27:45 2013

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME GERunDict
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "GERunDict.h"

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
   void GERun_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void *new_GERun(void *p = 0);
   static void *newArray_GERun(Long_t size, void *p);
   static void delete_GERun(void *p);
   static void deleteArray_GERun(void *p);
   static void destruct_GERun(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GERun*)
   {
      ::GERun *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GERun >(0);
      static ::ROOT::TGenericClassInfo 
         instance("GERun", ::GERun::Class_Version(), "./GERun.hh", 8,
                  typeid(::GERun), DefineBehavior(ptr, ptr),
                  &::GERun::Dictionary, isa_proxy, 4,
                  sizeof(::GERun) );
      instance.SetNew(&new_GERun);
      instance.SetNewArray(&newArray_GERun);
      instance.SetDelete(&delete_GERun);
      instance.SetDeleteArray(&deleteArray_GERun);
      instance.SetDestructor(&destruct_GERun);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GERun*)
   {
      return GenerateInitInstanceLocal((::GERun*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::GERun*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
TClass *GERun::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *GERun::Class_Name()
{
   return "GERun";
}

//______________________________________________________________________________
const char *GERun::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GERun*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GERun::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GERun*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void GERun::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GERun*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *GERun::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GERun*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
void GERun::Streamer(TBuffer &R__b)
{
   // Stream an object of class GERun.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GERun::Class(),this);
   } else {
      R__b.WriteClassBuffer(GERun::Class(),this);
   }
}

//______________________________________________________________________________
void GERun::ShowMembers(TMemberInspector &R__insp)
{
      // Inspect the data members of an object of class GERun.
      TClass *R__cl = ::GERun::IsA();
      if (R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*event", &event);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*cPlotEnergyHist", &cPlotEnergyHist);
      PACSSRun::ShowMembers(R__insp);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_GERun(void *p) {
      return  p ? new(p) ::GERun : new ::GERun;
   }
   static void *newArray_GERun(Long_t nElements, void *p) {
      return p ? new(p) ::GERun[nElements] : new ::GERun[nElements];
   }
   // Wrapper around operator delete
   static void delete_GERun(void *p) {
      delete ((::GERun*)p);
   }
   static void deleteArray_GERun(void *p) {
      delete [] ((::GERun*)p);
   }
   static void destruct_GERun(void *p) {
      typedef ::GERun current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GERun

/********************************************************
* GERunDict.cc
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

extern "C" void G__cpp_reset_tagtableGERunDict();

extern "C" void G__set_cpp_environmentGERunDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("GERun.hh");
  G__cpp_reset_tagtableGERunDict();
}
#include <new>
extern "C" int G__cpp_dllrevGERunDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* GERun */
static int G__GERunDict_656_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GERun* p = NULL;
   char* gvp = (char*) G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new GERun[n];
     } else {
       p = new((void*) gvp) GERun[n];
     }
   } else {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new GERun;
     } else {
       p = new((void*) gvp) GERun;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GERunDictLN_GERun));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GERunDict_656_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GERun* p = NULL;
   char* gvp = (char*) G__getgvp();
   //m: 1
   if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
     p = new GERun(*((string*) G__int(libp->para[0])));
   } else {
     p = new((void*) gvp) GERun(*((string*) G__int(libp->para[0])));
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GERunDictLN_GERun));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GERunDict_656_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) ((GERun*) G__getstructoffset())->GetEvent());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GERunDict_656_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) ((GERun*) G__getstructoffset())->GetEvent((int) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GERunDict_656_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) ((GERun*) G__getstructoffset())->GetNextEvent());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GERunDict_656_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GERun*) G__getstructoffset())->PlotEnergyHist();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GERunDict_656_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) GERun::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GERunDict_656_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GERun::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GERunDict_656_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) GERun::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GERunDict_656_0_10(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      GERun::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GERunDict_656_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GERun*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GERunDict_656_0_15(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GERun::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GERunDict_656_0_16(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) GERun::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GERunDict_656_0_17(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GERun::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GERunDict_656_0_18(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) GERun::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__GERunDict_656_0_19(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   GERun* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new GERun(*(GERun*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GERunDictLN_GERun));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef GERun G__TGERun;
static int G__GERunDict_656_0_20(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
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
       delete[] (GERun*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((GERun*) (soff+(sizeof(GERun)*i)))->~G__TGERun();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (GERun*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((GERun*) (soff))->~G__TGERun();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__GERunDict_656_0_21(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GERun* dest = (GERun*) G__getstructoffset();
   *dest = *(GERun*) libp->para[0].ref;
   const GERun& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* GERun */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncGERunDict {
 public:
  G__Sizep2memfuncGERunDict(): p(&G__Sizep2memfuncGERunDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncGERunDict::*p)();
};

size_t G__get_sizep2memfuncGERunDict()
{
  G__Sizep2memfuncGERunDict a;
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
extern "C" void G__cpp_setup_inheritanceGERunDict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__GERunDictLN_GERun))) {
     GERun *G__Lderived;
     G__Lderived=(GERun*)0x1000;
     {
       PACSSRun *G__Lpbase=(PACSSRun*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__GERunDictLN_GERun),G__get_linked_tagnum(&G__GERunDictLN_PACSSRun),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
     {
       TObject *G__Lpbase=(TObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__GERunDictLN_GERun),G__get_linked_tagnum(&G__GERunDictLN_TObject),(long)G__Lpbase-(long)G__Lderived,1,0);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableGERunDict() {

   /* Setting up typedef entry */
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__GERunDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__GERunDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GERunDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__GERunDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GERunDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__GERunDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__GERunDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GERunDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__GERunDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GERunDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<std::bidirectional_iterator_tag,TObject*,std::ptrdiff_t,const TObject**,const TObject*&>",117,G__get_linked_tagnum(&G__GERunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,std::ptrdiff_t,const TObject**,const TObject*&>",117,G__get_linked_tagnum(&G__GERunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*>",117,G__get_linked_tagnum(&G__GERunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,long>",117,G__get_linked_tagnum(&G__GERunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,long,const TObject**>",117,G__get_linked_tagnum(&G__GERunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("map<std::string,TObjArray*>",117,G__get_linked_tagnum(&G__GERunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("map<string,TObjArray*>",117,G__get_linked_tagnum(&G__GERunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("map<string,TObjArray*>",117,G__get_linked_tagnum(&G__GERunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("map<string,TObjArray*,less<string> >",117,G__get_linked_tagnum(&G__GERunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("pair<UInt_t,Int_t>",117,G__get_linked_tagnum(&G__GERunDictLN_pairlEunsignedsPintcOintgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<std::pair<UInt_t,Int_t> >",117,G__get_linked_tagnum(&G__GERunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<pair<UInt_t,Int_t> >",117,G__get_linked_tagnum(&G__GERunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__GERunDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GERunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__GERunDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GERunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<pair<unsigned int,int> >",117,G__get_linked_tagnum(&G__GERunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Float_t>",117,G__get_linked_tagnum(&G__GERunDictLN_TVectorTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Double_t>",117,G__get_linked_tagnum(&G__GERunDictLN_TVectorTlEdoublegR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTBase<Float_t>",117,G__get_linked_tagnum(&G__GERunDictLN_TMatrixTBaselEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTBase<Double_t>",117,G__get_linked_tagnum(&G__GERunDictLN_TMatrixTBaselEdoublegR),0,-1);
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* GERun */
static void G__setup_memvarGERun(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__GERunDictLN_GERun));
   { GERun *p; p=(GERun*)0x1000; if (p) { }
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GERunDictLN_GEEvent),-1,-1,2,"event=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GERunDictLN_TCanvas),-1,-1,2,"cPlotEnergyHist=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GERunDictLN_TClass),-1,-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarGERunDict() {
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
static void G__setup_memfuncGERun(void) {
   /* GERun */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__GERunDictLN_GERun));
   G__memfunc_setup("GERun",449,G__GERunDict_656_0_1, 105, G__get_linked_tagnum(&G__GERunDictLN_GERun), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GERun",449,G__GERunDict_656_0_2, 105, G__get_linked_tagnum(&G__GERunDictLN_GERun), -1, 0, 1, 1, 1, 0, "u 'string' - 0 - newFileName", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetEvent",802,G__GERunDict_656_0_3, 85, G__get_linked_tagnum(&G__GERunDictLN_GEEvent), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetEvent",802,G__GERunDict_656_0_4, 85, G__get_linked_tagnum(&G__GERunDictLN_GEEvent), -1, 0, 1, 1, 1, 0, "i - - 0 - nEvent", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetNextEvent",1217,G__GERunDict_656_0_5, 85, G__get_linked_tagnum(&G__GERunDictLN_GEEvent), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("PlotEnergyHist",1441,G__GERunDict_656_0_6, 121, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Class",502,G__GERunDict_656_0_7, 85, G__get_linked_tagnum(&G__GERunDictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (TClass* (*)())(&GERun::Class) ), 0);
   G__memfunc_setup("Class_Name",982,G__GERunDict_656_0_8, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GERun::Class_Name) ), 0);
   G__memfunc_setup("Class_Version",1339,G__GERunDict_656_0_9, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (Version_t (*)())(&GERun::Class_Version) ), 0);
   G__memfunc_setup("Dictionary",1046,G__GERunDict_656_0_10, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&GERun::Dictionary) ), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__GERunDictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TMemberInspector' - 1 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__GERunDict_656_0_14, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - ClassDef_StreamerNVirtual_b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__GERunDict_656_0_15, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GERun::DeclFileName) ), 0);
   G__memfunc_setup("ImplFileLine",1178,G__GERunDict_656_0_16, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&GERun::ImplFileLine) ), 0);
   G__memfunc_setup("ImplFileName",1171,G__GERunDict_656_0_17, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GERun::ImplFileName) ), 0);
   G__memfunc_setup("DeclFileLine",1152,G__GERunDict_656_0_18, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&GERun::DeclFileLine) ), 0);
   // automatic copy constructor
   G__memfunc_setup("GERun", 449, G__GERunDict_656_0_19, (int) ('i'), G__get_linked_tagnum(&G__GERunDictLN_GERun), -1, 0, 1, 1, 1, 0, "u 'GERun' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~GERun", 575, G__GERunDict_656_0_20, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 1);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__GERunDict_656_0_21, (int) ('u'), G__get_linked_tagnum(&G__GERunDictLN_GERun), -1, 1, 1, 1, 1, 0, "u 'GERun' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncGERunDict() {
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
extern "C" void G__cpp_setup_globalGERunDict() {
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

extern "C" void G__cpp_setup_funcGERunDict() {
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
G__linked_taginfo G__GERunDictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_TObject = { "TObject" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_string = { "string" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR = { "iterator<bidirectional_iterator_tag,TObject*,long,const TObject**,const TObject*&>" , 115 , -1 };
G__linked_taginfo G__GERunDictLN_TCanvas = { "TCanvas" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR = { "map<string,TObjArray*,less<string>,allocator<pair<const string,TObjArray*> > >" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_pairlEunsignedsPintcOintgR = { "pair<unsigned int,int>" , 115 , -1 };
G__linked_taginfo G__GERunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR = { "vector<pair<unsigned int,int>,allocator<pair<unsigned int,int> > >" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<pair<unsigned int,int>,allocator<pair<unsigned int,int> > >::iterator>" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_TVectorTlEfloatgR = { "TVectorT<float>" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_TVectorTlEdoublegR = { "TVectorT<double>" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_TMatrixTBaselEfloatgR = { "TMatrixTBase<float>" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_TMatrixTBaselEdoublegR = { "TMatrixTBase<double>" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_GEEvent = { "GEEvent" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_PACSSRun = { "PACSSRun" , 99 , -1 };
G__linked_taginfo G__GERunDictLN_GERun = { "GERun" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableGERunDict() {
  G__GERunDictLN_TClass.tagnum = -1 ;
  G__GERunDictLN_TBuffer.tagnum = -1 ;
  G__GERunDictLN_TMemberInspector.tagnum = -1 ;
  G__GERunDictLN_TObject.tagnum = -1 ;
  G__GERunDictLN_string.tagnum = -1 ;
  G__GERunDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__GERunDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__GERunDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__GERunDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__GERunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR.tagnum = -1 ;
  G__GERunDictLN_TCanvas.tagnum = -1 ;
  G__GERunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR.tagnum = -1 ;
  G__GERunDictLN_pairlEunsignedsPintcOintgR.tagnum = -1 ;
  G__GERunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR.tagnum = -1 ;
  G__GERunDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__GERunDictLN_TVectorTlEfloatgR.tagnum = -1 ;
  G__GERunDictLN_TVectorTlEdoublegR.tagnum = -1 ;
  G__GERunDictLN_TMatrixTBaselEfloatgR.tagnum = -1 ;
  G__GERunDictLN_TMatrixTBaselEdoublegR.tagnum = -1 ;
  G__GERunDictLN_GEEvent.tagnum = -1 ;
  G__GERunDictLN_PACSSRun.tagnum = -1 ;
  G__GERunDictLN_GERun.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableGERunDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__GERunDictLN_TClass);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_TObject);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_string);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_TCanvas);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_pairlEunsignedsPintcOintgR);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_vectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgR);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_reverse_iteratorlEvectorlEpairlEunsignedsPintcOintgRcOallocatorlEpairlEunsignedsPintcOintgRsPgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_TVectorTlEfloatgR);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_TVectorTlEdoublegR);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_TMatrixTBaselEfloatgR);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_TMatrixTBaselEdoublegR);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_GEEvent);
   G__get_linked_tagnum_fwd(&G__GERunDictLN_PACSSRun);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__GERunDictLN_GERun),sizeof(GERun),-1,324864,(char*)NULL,G__setup_memvarGERun,G__setup_memfuncGERun);
}
extern "C" void G__cpp_setupGERunDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupGERunDict()");
  G__set_cpp_environmentGERunDict();
  G__cpp_setup_tagtableGERunDict();

  G__cpp_setup_inheritanceGERunDict();

  G__cpp_setup_typetableGERunDict();

  G__cpp_setup_memvarGERunDict();

  G__cpp_setup_memfuncGERunDict();
  G__cpp_setup_globalGERunDict();
  G__cpp_setup_funcGERunDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncGERunDict();
  return;
}
class G__cpp_setup_initGERunDict {
  public:
    G__cpp_setup_initGERunDict() { G__add_setup_func("GERunDict",(G__incsetup)(&G__cpp_setupGERunDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initGERunDict() { G__remove_setup_func("GERunDict"); }
};
G__cpp_setup_initGERunDict G__cpp_setup_initializerGERunDict;

