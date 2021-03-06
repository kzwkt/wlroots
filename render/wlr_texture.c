#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wlr/render/interface.h>
#include <wlr/render/wlr_texture.h>

void wlr_texture_init(struct wlr_texture *texture,
		const struct wlr_texture_impl *impl) {
	assert(impl->get_size);
	assert(impl->write_pixels);
	texture->impl = impl;
}

void wlr_texture_destroy(struct wlr_texture *texture) {
	if (texture && texture->impl && texture->impl->destroy) {
		texture->impl->destroy(texture);
	} else {
		free(texture);
	}
}

struct wlr_texture *wlr_texture_from_pixels(struct wlr_renderer *renderer,
		enum wl_shm_format wl_fmt, uint32_t stride, uint32_t width,
		uint32_t height, const void *data) {
	return renderer->impl->texture_from_pixels(renderer, wl_fmt, stride, width,
		height, data);
}

struct wlr_texture *wlr_texture_from_wl_drm(struct wlr_renderer *renderer,
		struct wl_resource *data) {
	if (!renderer->impl->texture_from_wl_drm) {
		return NULL;
	}
	return renderer->impl->texture_from_wl_drm(renderer, data);
}

struct wlr_texture *wlr_texture_from_dmabuf(struct wlr_renderer *renderer,
		struct wlr_dmabuf_buffer_attribs *attribs) {
	if (!renderer->impl->texture_from_dmabuf) {
		return NULL;
	}
	return renderer->impl->texture_from_dmabuf(renderer, attribs);
}

void wlr_texture_get_size(struct wlr_texture *texture, int *width,
		int *height) {
	return texture->impl->get_size(texture, width, height);
}

bool wlr_texture_write_pixels(struct wlr_texture *texture,
		enum wl_shm_format wl_fmt, uint32_t stride, uint32_t width,
		uint32_t height, uint32_t src_x, uint32_t src_y, uint32_t dst_x,
		uint32_t dst_y, const void *data) {
	return texture->impl->write_pixels(texture, wl_fmt, stride, width, height,
		src_x, src_y, dst_x, dst_y, data);
}
