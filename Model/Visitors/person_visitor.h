#ifndef MODEL_VISITORS_PERSON_VISITOR_H_
#define MODEL_VISITORS_PERSON_VISITOR_H_

class Visitable;

class PersonVisitor {
 public:
  virtual void VisitLecturer(Visitable* visitable) = 0;
  virtual void VisitStudent(Visitable* visitable) = 0;
};

#endif  // MODEL_VISITORS_PERSON_VISITOR_H_
