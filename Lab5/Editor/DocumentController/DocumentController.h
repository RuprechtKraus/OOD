#pragma once
#include "CommandHistory/ICommandHistory.h"
#include "ResourceRepository/IResourceRepository.h"
#include "Document/IDocument.h"
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

namespace ph = std::placeholders;

enum class HandleResult
{
	Success,
	Error,
	Exit
};

class DocumentController
{
private:
	using CommandHandler = std::function<void(std::istream&)>;

public:
	DocumentController(
		IDocument& document, 
		ICommandHistory& history, 
		IResourceRepository& repository);

	HandleResult HandleCommand(std::istream& input);
	void ShowHelp() const;

private:
	void SetTitle(std::istream& args);
	void InsertParagraph(std::istream& args);
	void InsertImage(std::istream& args);
	void ReplaceText(std::istream& args);
	void ResizeImage(std::istream& args);
	void DeleteItem(std::istream& args);
	void Undo(std::istream& args);
	void Redo(std::istream& args);
	void List(std::istream& args) const;
	void Save(std::istream& args) const;
	void Help(std::istream& args) const;
	void Exit(std::istream& args) noexcept;

	IDocument& m_document;
	ICommandHistory& m_history;
	IResourceRepository& m_repository;
	HandleResult m_status = HandleResult::Success;

	const std::unordered_map<std::string, CommandHandler> m_commands{
		{ "settitle", std::bind(&DocumentController::SetTitle, this, ph::_1) },
		{ "insertparagraph", std::bind(&DocumentController::InsertParagraph, this, ph::_1) },
		{ "insertimage", std::bind(&DocumentController::InsertImage, this, ph::_1) },
		{ "replacetext", std::bind(&DocumentController::ReplaceText, this, ph::_1) },
		{ "resizeimage", std::bind(&DocumentController::ResizeImage, this, ph::_1) },
		{ "deleteitem", std::bind(&DocumentController::DeleteItem, this, ph::_1) },
		{ "undo", std::bind(&DocumentController::Undo, this, ph::_1) },
		{ "redo", std::bind(&DocumentController::Redo, this, ph::_1) },
		{ "list", std::bind(&DocumentController::List, this, ph::_1) },
		{ "save", std::bind(&DocumentController::Save, this, ph::_1) },
		{ "help", std::bind(&DocumentController::Help, this, ph::_1) },
		{ "exit", std::bind(&DocumentController::Exit, this, ph::_1) },
	};
};