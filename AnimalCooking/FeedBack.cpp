#include "FeedBack.h"

void FeedBack::draw()
{
	if (s1_->getSelect() != nullptr) {
		s1_->getSelect()->feedback();
	}
	if (s2_->getSelect() != nullptr) {
		s2_->getSelect()->feedback();
	}
}
