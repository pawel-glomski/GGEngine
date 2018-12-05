#pragma once

extern std::unique_ptr<Application> makeApplication();

int main()
{
	std::unique_ptr<Application> app = makeApplication();
	app->run();

	return 0;
}