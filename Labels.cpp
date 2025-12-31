#include "Labels.h"
#include "state.h"

std::string Labels::keyToFont(int key) {
	switch (key) {
		case 1:
			return "chatFont.fnt";
		case 2:
			return "gjFont01.fnt";
		case 3:
			return "gjFont02.fnt";
		case 4:
			return "gjFont03.fnt";
		case 5:
			return "gjFont04.fnt";
		case 6:
			return "gjFont05.fnt";
		case 7:
			return "gjFont06.fnt";
		case 8:
			return "gjFont07.fnt";
		case 9:
			return "gjFont08.fnt";
		case 10:
			return "gjFont09.fnt";
		case 11:
			return "gjFont10.fnt";
		case 12:
			return "gjFont11.fnt";
		case 0:
		default:
			return "bigFont.fnt";
	}
}

void Labels::updateFont() {

}

void Labels::createAttemptsLabel() {
	auto label = CCLabelBMFont::create("", this->keyToFont(setting().labelsFont).c_str());
	label->setTag(0x5603);
}