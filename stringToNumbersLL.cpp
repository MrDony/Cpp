#include <iostream>
#include <fstream>
#include <string>

using  namespace std;

template <class T>
struct node
{
  T m_data;
  node<T>* m_next{NULL};
};

template <class T>
class LinkedList
{
  node<T>* m_head{NULL};
  node<T>* m_tail{NULL};
  int m_size{0};
  void copy(LinkedList& p_LL)
  {
    node<T>* l_head=p_LL.m_head;
    while(l_head)
    {
      this->add(l_head->m_data);
      l_head=l_head->m_next;
    }
  }
  void burn()
  {
    while(m_head)
    {
        m_tail=m_head;
        m_head=m_head->m_next;
        delete m_tail;
    }
    m_head=NULL;
    m_tail=m_head;
  }
  bool doesContain(const T& p_ele)
  {
    node<T>* l_head=m_head;
    while(l_head)
    {
      if(l_head->m_data==p_ele)
        return true;
      l_head=l_head->m_next;
    }
    return false;
  }
public:
  LinkedList(){m_head=NULL;m_tail=m_head;m_size=0;}
  LinkedList(LinkedList& p_LL)
  {
    this->copy(p_LL);
  }
  node<T>* head(){return m_head;}
  void sortAcc()
  {
    node<T>* l_h1=m_head;
    node<T>* l_h2=m_head;
    while(l_h1)
    {
      l_h2=l_h1->m_next;
      while(l_h2)
      {
        if(l_h2->m_data<l_h1->m_data)
        {
          T swp=l_h2->m_data;
          l_h2->m_data=l_h1->m_data;
          l_h1->m_data=swp;
        }
        l_h2=l_h2->m_next;
      }
      l_h1=l_h1->m_next;
    }
  }
  void add(T p_ele)
  {
    if(m_head==NULL && m_tail==NULL)
    {
      m_head=new node<T>;
      m_head->m_data=p_ele;
      m_tail=m_head;
    }
    else
    {
      m_tail->m_next=new node<T>;
      m_tail=m_tail->m_next;
      m_tail->m_data=p_ele;
    }

    //cout<<"added = "<< p_ele<<"\t";
    m_size++;
    //cout<<"size = "<<m_size<<endl;
    return;
  }
  int size(){return m_size;}
  bool remove(T p_ele)
  {
    node<T>* l_head=m_head;
    node<T>* l_prevNode=NULL;
    if(l_head->m_data==p_ele)//removing head element
    {
      m_head=m_head->m_next;
      delete l_head;
      m_size--;
      return true;
    }
    bool found=false;
    while(l_head)
    {
      if(l_head->m_data==p_ele)
      {
        found=true;
        break;
      }
      l_prevNode=l_head;
      l_head=l_head->m_next;
      if(found)
      {
        l_prevNode=l_head->m_next;
        delete l_head;
        m_size--;
      }
      return found;
    }
  }
  node<T>* getNode(T p_ele)
  {
    node<T>* l_head=m_head;
    while(l_head)
    {
      if(l_head->m_data==p_ele)
        break;
      l_head=l_head->m_next;
    }
    return l_head;
  }
  void print()
  {
    int i=0;
    node<T>* l_head=m_head;
    while(l_head)
    {
      cout<<" ("<<i<<") "<<l_head->m_data<<"\t";
      l_head=l_head->m_next;
      i++;
    }

  }
  void push(T p_ele)
  {
    node<T>* l_head=new node<T>;
    l_head->m_data=p_ele;
    l_head->m_next=m_head;
    m_head=l_head;
  }
  void pop()
  {
    node<T>* l_head=m_head;
    m_head=m_head->m_next;
    delete l_head;
  }
  T seek()
  {
    return m_head->m_data;
  }
  T top(){return seek();}
  void enque(T p_ele)
  {
    add(p_ele);
  }
  T deque()
  {
    pop();
  }
  void operator=(LinkedList& p_LL)
  {
    this->copy(p_LL);
  }
  bool operator==(const T& p_ele)
  {
    return doesContain(p_ele);
  }
  T operator[](const int i)
  {
    node<T>* l_head=m_head;
    int j=0;
    while(1)
    {
      if(l_head==NULL)
      {
        cout<<"index out of range\n";
        T ret;
        return ret;
      }
      if(i==j)
        return l_head->m_data;
      l_head=l_head->m_next;
      j++;
    }
  }
  ~LinkedList()
  {burn();}
};



void intoLL(string data,LinkedList<string>& seperators, LinkedList<string>& to)
{
  cout<<data;

  cout<<endl;
  string toadd;
  string current;
  for(int i=0;i<data.length();i++)
  {
    current=data[i];
    if(data[i+1]=='\0')
      return;
    if(seperators==current)
    {
      to.add(toadd);
      toadd="\0";
      continue;
    }
    toadd+=current;
  }
}

float setDecimalPlace(float val, int dp)
{
  string v=to_string(val);
  string v2;
  bool decimalReached=false;
  int j=0;
  for(int i=0;i<v.length();i++)
  {
    if(v[i]=='.')
    {
      decimalReached=true;
    }
    if(decimalReached==true)
    {
      if(j==dp)
        break;
      j++;
    }
    v2+=v[i];
  }
  return stof(v2);
}

int main()
{
  int noOfCLasses=6;
  //const int dataDecPlaces=0;
  cout<<"ENTER NO OF CLASSES = ";
  cin>>noOfCLasses;
  cout<<endl;

  ifstream open("data_1.txt");
  string data;
  string line;
  while(!open.eof())
  {
    getline(open,line);
    data+=line;
    data+="\n";
  }

  open.close();
  LinkedList<string> seperators;
  seperators.add(" ");
  seperators.add("\n");
  //seperators.add("\0");
  //cout<<endl;
  //seperators.print();
  //cout<<endl;
  LinkedList<string> seperated;
  intoLL(data,seperators,seperated);
  //cout<<"\n--------------------------------------\n";
  //seperated.print();
  //cout<<"k"<<endl;


  float min=10000000;
  float max=-10000000;
  LinkedList<float> dataSet;
  node<string>* l_h;
  l_h=seperated.head();
  cout<<"\nCREATING DATA SET\n";
  while(l_h)
  {
    cout<<stof(l_h->m_data)<<endl;
    dataSet.add(std::stof(l_h->m_data));
    l_h=l_h->m_next;
  }
  cout<<"\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
  //dataSet.print();

  //cout<<endl<<dataSet.size()<<endl;
  dataSet.sortAcc();
  dataSet.print();
  //cout<<endl<<dataSet.size()<<endl;
  cout<<"\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

  node<float>* l_head=dataSet.head();
  while(l_head)
  {
    if(l_head->m_data<min)
      min=l_head->m_data;
    if(l_head->m_data>max)
      max=l_head->m_data;
    l_head=l_head->m_next;
    //cout<<endl<<dataSet.size()<<endl;
  }
  float range=max-min;
  float classW=range/noOfCLasses;

  //setprecision(dataDecPlaces);
  cout<<"Min = "<<min<<"\tMax = "<<max<<"\tRange= "<<range<<"\tClassW = "<<classW<<"\tData size = "<<dataSet.size()<<"\nEnter ClassW = ";
  cin>>classW;
  cout<<"\nCLASSES\n";
  float** l_classes = new float*[noOfCLasses];
  for(int i=0;i<noOfCLasses;i++)
    l_classes[i]=new float[2]{0};
  float gap=min;
  for(int i=0;i<noOfCLasses;i++)
  {
    cout<<gap<<"----";
    l_classes[i][0]=gap;
    gap+=classW;
    gap--;
    l_classes[i][1]=gap;
    cout<<gap;
    gap++;
    int freq=0;
    for(int j=0;j<dataSet.size();j++)
    {
      //cout<<endl<<dataSet[j]<<">="<<l_classes[i][0]<<" && "<<dataSet[j]<<"<="<<l_classes[i][1]<<endl;
      //cout<<"("<<dataSet[j]<<")_";
      if(dataSet[j]>=l_classes[i][0] && dataSet[j]<=l_classes[i][1])
      {
        freq++;
        cout<<" + "<<dataSet[j];
      }
    }
    cout<<" = "<<freq<<endl;
  }
  cout<<endl;

  return 0;
}
