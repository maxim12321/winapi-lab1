#include "person_container.h"

bool PersonContainer::Empty() const {
  return size_ == 0;
}

int PersonContainer::Size() const {
  return size_;
}
