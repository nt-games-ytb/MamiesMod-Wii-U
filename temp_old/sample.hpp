#include "curl.h"
#include "../src/mamiesmod/minecraft/mc.hpp"
#include "xf/DrawHelper.h"
#include "code/code.h"
#include "library/memory.hpp"

class MemoryStruct {
	char* memory;
	size_t size;

	MemoryStruct() {
		memory = (char*)mem::malloc(1);
		size = 0;
	}
};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	size_t real_size = size * nmemb;
	struct MemoryStruct* mem = (struct MemoryStruct*)userp;

	char* new_memory = (char*)mem::realloc(mem->memory, mem->size + real_size);
	if (new_memory == nullptr) { return 0; }

	mem::XMemCpy(new_memory + mem->size, contents, real_size);
	mem->memory = new_memory;
	mem->size += real_size;

	return real_size;
}

bool toggle = false;

extern "C"
void geticon()
{
	auto mc = mc::Minecraft::getInstance();
	auto tes = mc::Tesselator::getInstance()->getBuilder();

	mc::GlStateManager::matrixMode(1);
	mc::GlStateManager::loadIdentity();
	mc::GlStateManager::ortho(0.0, 640.0, 360.0, 0.0, 0.0, 3000.0);
	mc::GlStateManager::matrixMode(0);
	mc::GlStateManager::enableAlphaTest();
	mc::GlStateManager::alphaFunc(4, 0.1);
	mc::GlStateManager::enableDepthTest();
	mc::GlStateManager::depthFunc(3);
	mc::GlStateManager::depthMask(true);

	mc::GlStateManager::pushMatrix();
	mc::GlStateManager::translatef(50, 50, 0);
	mc::GlStateManager::scalef(84.8 * 2, 97.6 * 2, 1);
	mc::GlStateManager::bindTexture(5000);
	tes->begin();
	tes->color(-1, 0xFF);
	tes->vertexUV(0, 1, -90, 0, 1);
	tes->vertexUV(1, 1, -90, 1, 1);
	tes->vertexUV(1, 0, -90, 1, 0);
	tes->vertexUV(0, 0, -90, 0, 0);
	tes->end();
	mc::GlStateManager::popMatrix();

		if (!toggle) {
			toggle = true;

			CURL* curl = curl_easy_init();
			if (curl) {

				MemoryStruct chunk = MemoryStruct();

				curl_easy_setopt(curl, CURLOPT_URL, "http://fch.starfree.jp/o.png");
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

				int res = curl_easy_perform(curl);

				curl_easy_cleanup(curl);

				auto buffer_image = mc::BufferedImage(nullptr, chunk.memory, chunk.size);
				mc::Textures::loadTexture(&buffer_image, 5000);

				mem::free(chunk.memory);
			}
		}
	else { toggle = false; }

	mc::GlStateManager::disableAlphaTest();
	mc::GlStateManager::depthMask(false);
}