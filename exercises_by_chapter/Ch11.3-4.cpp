#include <cstdio>
#include <memory>

using File_sptr = std::shared_ptr<FILE>;

struct Hal {
	Hal(File_sptr file);
	~Hal();
	void write_status();
	File_sptr file;
};

Hal::Hal(File_sptr file) {
	this->file = file;
}

Hal::~Hal() {
	fprintf(this->file.get(), "Stop, Dave\n");
}

void Hal::write_status() {
	fprintf(this->file.get(), "I'm completely operational\n");
}

int main() {
	auto file = fopen("HAL9000", "w");
	if (!file)return errno;
	File_sptr file_ptr{ file , fclose };

	Hal a{ file_ptr };
	{
		Hal b{ file_ptr };
		b.write_status();
	}
	a.write_status();
	Hal c{ file_ptr };
}