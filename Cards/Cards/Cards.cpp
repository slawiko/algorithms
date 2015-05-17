#include <iostream>
#include <fstream>

using namespace std;

// LIST TEMPLATE !!!
template <class T1,class T2> class KList;
template <class T1,class T2> ostream& operator << (ostream &stream,const KList<T1,T2> &Obj);

template <class T1,class T2> struct KNode{
	T1   key; // INDEX
	T2 value; // COLOR
	KNode*  next;
};

template <class T1,class T2> class KList{
	
    KNode<T1,T2>  *f,**e;
public:
	KList(){f=0;e=&f;};
	~KList(){Clear();};
     KList(const KList &Obj);

	void Copy(const KList &Obj);
	void Push_Front(T1 aKey,T2 aValue);
	void Push_Back(T1 aKey,T2 aValue);
	KNode<T1,T2>* Pop_Front();
	bool IsEmpty(){return f==0;};
	void Delete(T1 aKey);
	int Size();
    void PrintL();
	void Clear();
	bool PoiskL(T1 aKey);
	
	T2& operator [] (T1 k);
 KList& operator = (const KList &Obj);
	
	friend ostream& operator << (ostream &stream,const KList &Obj);
		
};

template <class T1,class T2> KList<T1,T2>::KList(const KList &Obj){
		f=0;
		e=&f;
	    Copy(Obj);
	};

template <class T1,class T2> void KList<T1,T2>::Copy(const KList &Obj){
		KNode<T1,T2> *p;
		p=Obj.f;
		while (p!=0){
			Push_Back(p->key,p->value);
			p=p->next;
		}
		   
	};
	
template <class T1,class T2> 	void KList<T1,T2>::Push_Front(T1 aKey,T2 aValue){
		KNode<T1,T2>* p;
	    p = new KNode<T1,T2>;
	    p->key=aKey;
	    p->value=aValue;
		p->next=f;
		if (e==&f)
        e=&p->next;
		f=p;
	};

template <class T1,class T2> 	void KList<T1,T2>::Push_Back(T1 aKey,T2 aValue){
		KNode<T1,T2> *p;
		p = new KNode<T1,T2>;
		p->key=aKey;
		p->value=aValue;
		p->next=0;
		*e=p;
		e=&p->next;
		if (f==0)
			f=p;
	};

template <class T1,class T2>    KNode<T1,T2>* KList<T1,T2>::Pop_Front(){
	if (!IsEmpty()){
		KNode<T1,T2> *p;
		p=f;
		f=p->next;
		if (f==0)
			e=&f;
		return p;
	}
	return 0;
}

template <class T1,class T2> 	void KList<T1,T2>::Delete(T1 aKey){
		KNode<T1,T2>* p;
	    KNode<T1,T2>** pp;
	    pp=&f;
	    p=f;
	    while (p!=0){
			if (p->key==aKey){
			*pp=p->next;
			if (*pp==*e)
				e=pp;
			delete p;
		    p=*pp;
			}
		else {
			pp=&(p->next);
			p=p->next;
		}
		}
	};
	
template <class T1,class T2> 	int KList<T1,T2>::Size(){
		KNode<T1,T2>* p;
	    int i;
	    p=f;
	    i=0;
	    while (p!=0){
			p=p->next;
		    ++i;
		}
	    return i;
	};
    
template <class T1,class T2> 	void KList<T1,T2>::PrintL(){
		KNode<T1,T2>* p;
	    p=f;
 	    while (p!=0){
			cout << p->key << " " << p->value << "   ";
		    p=p->next;
		}
	};
	
template <class T1,class T2> 	T2& KList<T1,T2>::operator [] (T1 k){
		KNode<T1,T2>* p;
		p=f;
		while ((p!=0) && (p->key!=k))
			p=p->next;
		return p->value;
	};
	
template <class T1,class T2> 	KList<T1,T2>& KList<T1,T2>::operator = (const KList &Obj){
		if (this!=&Obj){
			Clear();
			Copy(Obj);
		} 
	    return *this;
	};
	
template <class T1,class T2> 	ostream& operator << (ostream &stream,const KList<T1,T2> &Obj){
		KNode<T1,T2>* p;
		p=Obj.f;
		while (p!=0){
			stream << p->key << " " << p->value << "   ";
		    p=p->next;
		}
		return stream;
	};

template <class T1,class T2> 	void KList<T1,T2>::Clear(){
		KNode<T1,T2> *p;
		while (f!=0){
			p=f;
			f=p->next;
			delete p;
		}
	}; 

template <class T1,class T2> 	bool KList<T1,T2>::PoiskL(T1 aKey){
		KNode<T1,T2> *p;
		p=f;
		while (p!=0){
			if (aKey==p->key)
				return true;
			p=p->next;
		}
		return false;
	};


int main(int argc, char* argv[])
{   
	ifstream In("In.txt",ios::in);
	int i,n;
    In >> n;
	cout << "N Is:" << endl;
	cout << n << endl;
	KList<int,int> L;
	KNode<int,int>* p;
	for (i=0;i<n;++i)
		L.Push_Back(i,0);
	
	int j=0;     // schetchik
	int color=0; // COLOR
	int* res=new int[n]; // Resul Stopka Pokrashennix Cartochek
	
	while (!L.IsEmpty()) {
		p=L.Pop_Front();
		res[p->key]=color;
		color=1-color;
        delete p;    
 		p=L.Pop_Front();
		if (!L.IsEmpty())
		L.Push_Back(p->key,p->value);
		else res[p->key]=color;
		delete p;
		//L.Size();
	}
	//////////////////////////////
	cout << "Result Is:" << endl ;
	for (i=0;i<n;++i)
		cout << res[i] << " ";
	//////////////////////////////
	ofstream Out("Out.txt",ios::out);
	for (i=0;i<n;++i)
		Out << res[i] << " " ;



	return 0;
}