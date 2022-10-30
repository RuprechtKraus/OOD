#include "Command/Command.h"
#include "CommandHistory/CommandHistory.h"
#include "Document/Document.h"
#include "Document/DocumentItem.h"
#include "Document/Elements/Image.h"
#include "Document/Elements/Paragraph.h"
#include "ResourceRepository/ResourceRepository.h"
#include <iostream>

int main()
{
	Document document;
	ResourceRepository imageRepository(R"(images)");

	return 0;
}