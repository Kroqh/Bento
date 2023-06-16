#include <Bento.h>

class Sandbox : public Bento::Application
{
public:
	Sandbox() {

	}
	~Sandbox() {

	}
};

Bento::Application* Bento::CreateApplication() {
	return new Sandbox();
}