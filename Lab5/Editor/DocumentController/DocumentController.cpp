#include "DocumentController.h"
#include "Command/Command.h"
#include "Utils/StringUtils.h"
#include <format>

DocumentController::DocumentController(
	IDocument& document,
	ICommandHistory& history,
	IResourceRepository& repository)
	: m_document(document)
	, m_history(history)
	, m_repository(repository)
{
}

HandleResult DocumentController::HandleCommand(std::istream& input)
{
	std::string command;
	input >> command;

	command = StringUtils::ToLower(command);
	auto it = m_commands.find(command);
	m_status = HandleResult::Success;

	if (it != m_commands.end())
	{
		try
		{
			it->second(input);
		}
		catch (const std::exception& e)
		{
			std::cout << "Cannot handle command: " << e.what() << std::endl;
			m_status = HandleResult::Error;
		}
	}
	else
	{
		std::cout << "Unknown command" << std::endl;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		m_status = HandleResult::Error;
	}

	return m_status;
}

void DocumentController::ShowHelp() const
{
	std::cout << "Commands: \n"
			  << "SetTitle <title>\n"
			  << "InsertParagraph <position>|end <text>\n"
			  << "InsertImage <position>|end <width> <height> <path>\n"
			  << "ReplaceText <position> <text>\n"
			  << "ResizeImage <position> <width> <height>\n"
			  << "DeleteItem <position>\n"
			  << "Undo\n"
			  << "Redo\n"
			  << "List\n"
			  << "Save <path>\n"
			  << "Help\n"
			  << "Exit" << std::endl;
}

void DocumentController::SetTitle(std::istream& args)
{
	std::string title;
	args >> std::ws;
	std::getline(args, title);
	auto command = std::make_unique<SetTitleCommand>(m_document, title);

	command->Execute();
	m_history.AddCommand(std::move(command));
}

void DocumentController::InsertParagraph(std::istream& args)
{
	std::string position;
	std::string text;

	args >> position >> std::ws;
	std::getline(args, text);

	std::unique_ptr<InsertParagraphCommand> command;

	if (StringUtils::ToLower(position) == "end")
	{
		command = std::make_unique<InsertParagraphCommand>(m_document, text);
	}
	else
	{
		command = std::make_unique<InsertParagraphCommand>(m_document, text, std::stoi(position));
	}

	command->Execute();
	m_history.AddCommand(std::move(command));
}

void DocumentController::InsertImage(std::istream& args)
{
	std::string position;
	std::string path;
	int width;
	int height;

	args >> position >> width >> height >> std::ws;
	std::getline(args, path);

	std::unique_ptr<InsertImageCommand> command;

	if (StringUtils::ToLower(position) == "end")
	{
		command = std::make_unique<InsertImageCommand>(m_document, m_repository,
			path, width, height);
	}
	else
	{
		command = std::make_unique<InsertImageCommand>(m_document, m_repository,
			path, width, height, std::stoi(position));
	}

	command->Execute();
	m_history.AddCommand(std::move(command));
}

void DocumentController::ReplaceText(std::istream& args)
{
	std::string text;
	int index;

	args >> index >> std::ws;
	std::getline(args, text);

	auto command = std::make_unique<ReplaceTextCommand>(m_document, text, index);
	command->Execute();
	m_history.AddCommand(std::move(command));
}

void DocumentController::ResizeImage(std::istream& args)
{
	int index;
	int width;
	int height;

	args >> index >> width >> height;

	auto command = std::make_unique<ResizeImageCommand>(m_document, width, height, index);
	command->Execute();
	m_history.AddCommand(std::move(command));
}

void DocumentController::DeleteItem(std::istream& args)
{
	int index;
	args >> index;

	auto command = std::make_unique<DeleteItemCommand>(m_document, index);
	command->Execute();
	m_history.AddCommand(std::move(command));
}

void DocumentController::Undo(std::istream& args)
{
	m_document.Undo();
}

void DocumentController::Redo(std::istream& args)
{
	m_document.Redo();
}

void DocumentController::List(std::istream&) const
{
	std::cout << "Title: " << m_document.GetTitle() << '\n';

	for (size_t i = 0; i < m_document.GetItemsCount(); i++)
	{
		auto item = m_document.GetItem(i);

		std::cout << i << ". ";

		if (item.GetParagraph())
		{
			auto paragraph = item.GetParagraph();
			std::cout << std::format("Paragraph: {}", paragraph->GetText());
			std::cout << '\n';
		}
		else
		{
			auto image = item.GetImage();
			std::cout << std::format("Image: {} {} {}",
				image->GetWidth(),
				image->GetHeight(),
				image->GetPath().string());
			std::cout << '\n';
		}
	}
}

void DocumentController::Save(std::istream& args) const
{
	std::string path;
	args >> std::ws;
	std::getline(args, path);
	m_document.Save(path);
}

void DocumentController::Help(std::istream&) const
{
	ShowHelp();
}

void DocumentController::Exit(std::istream&) noexcept
{
	m_status = HandleResult::Exit;
}