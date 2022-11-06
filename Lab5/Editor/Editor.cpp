#include "CommandHistory/CommandHistory.h"
#include "Document/Document.h"
#include "DocumentController/DocumentController.h"
#include "ResourceRepository/ResourceRepository.h"
#include <iostream>
#include <sstream>

int main()
{
	ResourceRepository imageRepository("images");
	CommandHistory history;
	Document document(history);
	DocumentController controller(document, history, imageRepository);
	HandleResult handleResult = HandleResult::Success;

	controller.ShowHelp();

	do
	{
		std::cout << "> ";
	} while ((handleResult = controller.HandleCommand(std::cin)) != HandleResult::Exit);
}