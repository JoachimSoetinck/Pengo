#pragma once
namespace dae
{
	class Command
	{
	public:
		explicit Command() = default;
		virtual ~Command() = default;
		virtual void Execute() = 0;

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;
	};



	class TestCommand : public Command
	{
	public:
		TestCommand();
		void Execute() override;
	};
}