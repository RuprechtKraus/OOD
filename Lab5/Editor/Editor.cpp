#include "Document/Document.h"
#include "Document/DocumentItem.h"
#include "Document/Elements/Image.h"
#include "Document/Elements/Paragraph.h"
#include "Command/Command.h"
#include <iostream>
#include "ResourceRepository/ResourceRepository.h"

int main()
{
	Document document;
	ResourceRepository imageRepository(R"(images)");

	InsertImageCommand insertImage1(document, imageRepository,
		R"(C:\Users\Ruprecht Kraus\Desktop\Wallpapers\3dQ4Wt0iEg8.jpg)",
		100, 100);
	insertImage1.Execute();

	InsertImageCommand insertImage2(document, imageRepository,
		R"(C:\Users\Ruprecht Kraus\Desktop\Wallpapers\464895-VV3.jpg)",
		100, 100);
	insertImage2.Execute();

	ResizeImageCommand resizeImage1(document, 250, 250, 0);
	ResizeImageCommand resizeImage2(document, 500, 500, 1);

	resizeImage1.Execute();
	resizeImage2.Execute();

	resizeImage1.Revert();
	resizeImage2.Revert();

	return 0;
}