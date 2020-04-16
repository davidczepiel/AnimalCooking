#include "FeedBack.h"

void FeedBack::draw()
{
	if (s1_->getSelect() != nullptr) {
		s1_->getSelect()->feedback(Resources::Player1);
	}
	if (s2_->getSelect() != nullptr) {
		s2_->getSelect()->feedback(Resources::Player2);
	}
}
