#include "Document/Document.h"
#include "Document/DocumentItem.h"
#include "Document/Elements/Image.h"
#include "Document/Elements/Paragraph.h"
#include "Command/InsertImageCommand.h"
#include <iostream>
#include "ResourceRepository/ResourceRepository.h"

int main()
{
	Document document;
	ResourceRepository imageRepository(R"(images)");

	InsertImageCommand imageCommand(document, imageRepository,
		R"(C:\Users\Ruprecht Kraus\Desktop\Wallpapers\3dQ4Wt0iEg8.jpg)",
		100, 100);

	imageCommand.Execute();

	return 0;
}