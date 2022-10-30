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
	CommandHistory history;
	Document document(history);
	ResourceRepository imageRepository(R"(images)");

	InsertImageCommand imageCommand1(document, imageRepository, 
		R"(C:\Users\Ruprecht Kraus\Desktop\Wallpapers\5563f5c1bf997c6e6513873347bf2af3.png)", 
		100, 100);
	imageCommand1.Execute();

	InsertParagraphCommand paragraphCommand1(document, "First paragraph");
	paragraphCommand1.Execute();

	InsertParagraphCommand paragraphCommand2(document, "Second paragraph");
	paragraphCommand2.Execute();

	InsertParagraphCommand paragraphCommand3(document, "Third paragraph", 1);
	paragraphCommand3.Execute();

	InsertImageCommand imageCommand2(document, imageRepository,
		R"(C:\Users\Ruprecht Kraus\Desktop\Wallpapers\464895-VV3.jpg)",
		100, 100);
	imageCommand2.Execute();

	paragraphCommand3.Revert();

	document.Save(R"(C:\Users\Ruprecht Kraus\Documents\document.html)");

	return 0;
}