#include "wsi_platform.hpp"
#include "vulkan/vulkan.h"
#include <SDL3/SDL_vulkan.h>

#if defined(__APPLE__)
#include <SDL3/SDL_syswm.h>
#include <vulkan/vulkan_metal.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>
#endif

VkSurfaceKHR SDL_WSIPlatform::create_surface(VkInstance instance, VkPhysicalDevice gpu)
{
#if defined(__APPLE__)
	(void)gpu;
	VkSurfaceKHR surface = nullptr;

	SDL_SysWMinfo wmInfo;
	SDL_GetWindowWMInfo(window, &wmInfo, SDL_SYSWM_CURRENT_VERSION);
	NSWindow *nswindow = wmInfo.info.cocoa.window;

	id view = [nswindow contentView];

	if (![view wantsLayer])
		[view setWantsLayer:YES];

	if (![[view layer] isKindOfClass:[CAMetalLayer class]])
		[view setLayer:[CAMetalLayer layer]];

	CAMetalLayer* metalLayer = (CAMetalLayer*)[view layer];

	VkMetalSurfaceCreateInfoEXT createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT;
	createInfo.pLayer = metalLayer;

	PFN_vkCreateMetalSurfaceEXT vkCreateMetalSurfaceEXT =
		(PFN_vkCreateMetalSurfaceEXT)vkGetInstanceProcAddr(instance, "vkCreateMetalSurfaceEXT");

	if (!vkCreateMetalSurfaceEXT)
	{
		printf("Failed to get vkCreateMetalSurfaceEXT.\n");
		return nullptr;
	}

	if (vkCreateMetalSurfaceEXT(instance, &createInfo, nullptr, &surface) != VK_SUCCESS)
	{
		printf("Error creating Metal surface\n");
		return nullptr;
	}

	return surface;
#else
	VkSurfaceKHR surface = nullptr;
	bool result = SDL_Vulkan_CreateSurface(window, instance, NULL, &surface);
	if (result != true)
	{
		printf("Error creating surface\n");
	}
	return surface;
#endif
}

void SDL_WSIPlatform::destroy_surface(VkInstance instance, VkSurfaceKHR surface)
{
	vkDestroySurfaceKHR(instance, surface, nullptr);
}

std::vector<const char *> SDL_WSIPlatform::get_instance_extensions()
{

	unsigned int extensionCount = 0;
	char const *const *extensions = SDL_Vulkan_GetInstanceExtensions(&extensionCount);
	if (extensions == NULL)
	{
		printf("Error getting instance extensions\n");
	}

	std::vector<const char *> extensionNames;
	for (unsigned int i = 0; i < extensionCount; ++i)
	{
		extensionNames.push_back(extensions[i]);
	}
	return extensionNames;
}

uint32_t SDL_WSIPlatform::get_surface_width()
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	return w;
}

uint32_t SDL_WSIPlatform::get_surface_height()
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	return h;
}

bool SDL_WSIPlatform::alive(Vulkan::WSI &wsi)
{
	return true;
}

void SDL_WSIPlatform::poll_input()
{
}

void SDL_WSIPlatform::poll_input_async(Granite::InputTrackerHandler *handler)
{
}

void SDL_WSIPlatform::set_window(SDL_Window *_window)
{
	window = _window;
}

void SDL_WSIPlatform::do_resize()
{
	resize = true;
}