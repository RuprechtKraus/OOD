#include "Document/Document.h"
#include "Document/DocumentItem.h"
#include "Document/Elements/Image.h"
#include "Document/Elements/Paragraph.h"
#include <iostream>

int main()
{
	Document document;

	document.InsertParagraph("Chapter 1");
	document.InsertParagraph("Chapter 2");
	document.InsertParagraph("Chapter 3");

	document.InsertImage("Image 1", 10, 10);
	document.InsertImage("Image 2", 20, 20);
	document.InsertImage("Image 3", 30, 30);

	return 0;
}