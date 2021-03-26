
#include <iostream>
#include "Container.h"

using namespace std;

void show(const Vector<int>& v)
{
  for(auto i : v) cout << i << " ";
  cout << "\n";
}


int main() {

  std::init<int> init = { 1,2,4,5 };
  STDList<int> list = { 1,2,4,5 };
  STDVector<int> vector = { 1,2,4,5 };
  STDDeque<int> deque = { 1,2,4,5 };
  List<int> list2 = { 1,2,4,5 };
  Vector<int> vector2 = { 1,2,4,5 };
  Deque<int> deque2 = { 1,2,4,5 };

  const STDInit<int> cinit = { 1,2,4,5 };
  const STDList<int> clist = { 1,2,4,5 };
  const STDVector<int> cvector = { 1,2,4,5 };
  const STDDeque<int> cdeque = { 1,2,4,5 };
  const List<int> clist2 = { 1,2,4,5 };
  const Vector<int> cvector2 = { 1,2,4,5 };
  const Deque<int> cdeque2 = { 1,2,4,5 };

  Vector<int> c1 = { 1,2,3,3,3,6,7,8,9,10,11,7,8 };
  Vector<int> c2 = init;
  Vector<int> c16 = cinit;
  Vector<int> c6 = std::move(init);
  Vector<int> c23 = std::move(cinit);

  Vector<int> c3 = list;
  Vector<int> c17 = clist;
  Vector<int> c7 = std::move(list);
  Vector<int> c24 = std::move(clist);
  Vector<int> c13 = list2;
  Vector<int> c20 = clist2;
  Vector<int> c10 = std::move(list2);
  Vector<int> c27 = std::move(clist2);

  Vector<int> c4 = vector;
  Vector<int> c14 = cvector;
  Vector<int> c8 = std::move(vector);
  Vector<int> c11 = std::move(cvector);
  Vector<int> c18 = vector2;
  Vector<int> c21 = cvector2;
  Vector<int> c25 = std::move(vector2);
  Vector<int> c28 = std::move(cvector2);

  Vector<int> c5 = deque;
  Vector<int> c15 = cdeque;
  Vector<int> c9 = std::move(deque);
  Vector<int> c12 = std::move(cdeque);
  Vector<int> c19 = deque2;
  Vector<int> c22 = cdeque2;
  Vector<int> c26 = std::move(deque2);
  Vector<int> c29 = std::move(cdeque2);

  const Vector<int> c01 = { 1,2,3 };
  const Vector<int> c02 = init;
  const Vector<int> c016 = cinit;
  const Vector<int> c06 = std::move(init);
  const Vector<int> c023 = std::move(cinit);

  const Vector<int> c03 = list;
  const Vector<int> c017 = clist;
  const Vector<int> c07 = std::move(list);
  const Vector<int> c024 = std::move(clist);
  const Vector<int> c013 = list2;
  const Vector<int> c020 = clist2;
  const Vector<int> c010 = std::move(list2);
  const Vector<int> c027 = std::move(clist2);

  const Vector<int> c04 = vector;
  const Vector<int> c014 = cvector;
  const Vector<int> c08 = std::move(vector);
  const Vector<int> c011 = std::move(cvector);
  const Vector<int> c018 = vector2;
  const Vector<int> c021 = cvector2;
  const Vector<int> c025 = std::move(vector2);
  const Vector<int> c028 = std::move(cvector2);

  const Vector<int> c05 = deque;
  const Vector<int> c015 = cdeque;
  const Vector<int> c09 = std::move(deque);
  const Vector<int> c012 = std::move(cdeque);
  const Vector<int> c019 = deque2;
  const Vector<int> c022 = cdeque2;
  const Vector<int> c026 = std::move(deque2);
  const Vector<int> c029 = std::move(cdeque2);


  List<int> l1 = { 1,2,4,5 };
  List<int> l2 = init;
  List<int> l16 = cinit;
  List<int> l6 = std::move(init);
  List<int> l23 = std::move(cinit);

  List<int> l3 = list;
  List<int> l17 = clist;
  List<int> l7 = std::move(list);
  List<int> l24 = std::move(clist);
  List<int> l13 = list2;
  List<int> l20 = clist2;
  List<int> l10 = std::move(list2);
  List<int> l27 = std::move(clist2);

  List<int> l4 = vector;
  List<int> l14 = cvector;
  List<int> l8 = std::move(vector);
  List<int> l11 = std::move(cvector);
  List<int> l18 = vector2;
  List<int> l21 = cvector2;
  List<int> l25 = std::move(vector2);
  List<int> l28 = std::move(cvector2);

  List<int> l5 = deque;
  List<int> l15 = cdeque;
  List<int> l9 = std::move(deque);
  List<int> l12 = std::move(cdeque);
  List<int> l19 = deque2;
  List<int> l22 = cdeque2;
  List<int> l26 = std::move(deque2);
  List<int> l29 = std::move(cdeque2);

  const List<int> l01 = { 1,2,4,5 };
  const List<int> l02 = init;
  const List<int> l016 = cinit;
  const List<int> l06 = std::move(init);
  const List<int> l023 = std::move(cinit);
              
  const List<int> l03 = list;
  const List<int> l017 = clist;
  const List<int> l07 = std::move(list);
  const List<int> l024 = std::move(clist);
  const List<int> l013 = list2;
  const List<int> l020 = clist2;
  const List<int> l010 = std::move(list2);
  const List<int> l027 = std::move(clist2);
              
  const List<int> l04 = vector;
  const List<int> l014 = cvector;
  const List<int> l08 = std::move(vector);
  const List<int> l011 = std::move(cvector);
  const List<int> l018 = vector2;
  const List<int> l021 = cvector2;
  const List<int> l025 = std::move(vector2);
  const List<int> l028 = std::move(cvector2);
              
  const List<int> l05 = deque;
  const List<int> l015 = cdeque;
  const List<int> l09 = std::move(deque);
  const List<int> l012 = std::move(cdeque);
  const List<int> l019 = deque2;
  const List<int> l022 = cdeque2;
  const List<int> l026 = std::move(deque2);
  const List<int> l029 = std::move(cdeque2);


  Deque<int> d1 = { 1,2,4,5 };
  Deque<int> d2 = init;
  Deque<int> d16 = cinit;
  Deque<int> d6 = std::move(init);
  Deque<int> d23 = std::move(cinit);
             
  Deque<int> d3 = list;
  Deque<int> d17 = clist;
  Deque<int> d7 = std::move(list);
  Deque<int> d24 = std::move(clist);
  Deque<int> d13 = list2;
  Deque<int> d20 = clist2;
  Deque<int> d10 = std::move(list2);
  Deque<int> d27 = std::move(clist2);
             
  Deque<int> d4 = vector;
  Deque<int> d14 = cvector;
  Deque<int> d8 = std::move(vector);
  Deque<int> d11 = std::move(cvector);
  Deque<int> d18 = vector2;
  Deque<int> d21 = cvector2;
  Deque<int> d25 = std::move(vector2);
  Deque<int> d28 = std::move(cvector2);
             
  Deque<int> d5 = deque;
  Deque<int> d15 = cdeque;
  Deque<int> d9 = std::move(deque);
  Deque<int> d12 = std::move(cdeque);
  Deque<int> d19 = deque2;
  Deque<int> d22 = cdeque2;
  Deque<int> d26 = std::move(deque2);
  Deque<int> d29 = std::move(cdeque2);

  show(c1);
  c1.remove({ 3, 3, 3 });
  show(c1);
  c1.remove(1);
  show(c1);
  c1.remove(std::list<int>({9,10}));
  show(c1);
  c1.remove(List<int>({ 7,8 }));
  show(c1);
  c1.remove([](const auto& item) {return item < 5; });
  show(c1);
  c1.erase(0, 2);
  show(c1);

  c1.add({ 1,2,3,4 });
  c1.add(init);
  c1.add(cinit);
  c1.add(std::move(init));
  c1.add(std::move(cinit));

  c1.add(list);
  c1.add(clist);
  c1.add(std::move(list));
  c1.add(std::move(clist));
  c1.add(list2);
  c1.add(clist2);
  c1.add(std::move(list2));
  c1.add(std::move(clist2));

  c1.add(vector);
  c1.add(cvector);
  c1.add(std::move(vector));
  c1.add(std::move(cvector));
  c1.add(vector2);
  c1.add(cvector2);
  c1.add(std::move(vector2));
  c1.add(std::move(cvector2));


  return 0;
}