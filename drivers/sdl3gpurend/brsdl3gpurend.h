#ifndef _BRSDL3GPUREND_H_
#define _BRSDL3GPUREND_H_

#ifndef _BRENDER_H_
#error Please include brender.h first
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * SDL3 GPU device info. Pointers refer to SDL3 objects:
 *   gpu_device               -> SDL_GPUDevice*
 *   window                   -> SDL_Window*
 *   swapchain_texture_format -> SDL_GPUTextureFormat (swapchain format)
 */
typedef struct SDL3GPUREND_DeviceInfo {
    void* gpu_device;
    void* window;
    uint32_t swapchain_texture_format;
} SDL3GPUREND_DeviceInfo;

void SDL3GPUREND_GetDeviceInfo(SDL3GPUREND_DeviceInfo* info);

/*
 * External render callback, invoked inside the driver's frame after the
 * swapchain texture has been acquired and the offscreen frame has been
 * blitted into it. Arguments:
 *   cmd                -> active SDL_GPUCommandBuffer*
 *   swapchain_texture  -> SDL_GPUTexture* of the acquired swapchain texture
 *                         (NULL if none was acquired this frame)
 *   w, h               -> swapchain texture size in pixels
 *   ud                 -> opaque user pointer
 *
 * The callback may begin its own render pass against swapchain_texture
 * (e.g. an ImGui overlay) before the command buffer is submitted.
 */
void SDL3GPUREND_SetExternalRenderCallback(void (*cb)(void* cmd, void* swapchain_texture, uint32_t w, uint32_t h, void* ud), void* ud);

/*
 * 3-window cockpit auxiliary render callback, invoked inside the driver's
 * Present for each aux window after the main window blit. The callback must
 * render the scene into transferTexture via BrZbSceneRenderBegin/End.
 *   viewIndex  -> 0 = left, 1 = right
 *   ud         -> opaque user pointer
 */
struct _VIDEO;
void SDL3GPUREND_SetAuxRenderCallback(struct _VIDEO* hVideo,
    void (*cb)(int viewIndex, void* ud), void* ud);

/*
 * Detached map screen render callback, invoked inside the driver's Present for
 * the map window after the main window blit. The callback must draw the map 2D
 * content into its own scratch buffer (the game back buffer's pixels are NULL
 * during Present) and call SDL3GPUREND_MapScreenUpload with the resulting
 * BGRA8888 pixels; the driver then clears transferTexture, composites the map
 * texture and blits it to the map window.
 *   ud -> opaque user pointer
 */
void SDL3GPUREND_SetMapRenderCallback(struct _VIDEO* hVideo,
    void (*cb)(void* ud), void* ud);

/*
 * Uploads BGRA8888 pixels into the driver's dedicated map window texture.
 * The map window composite draws this texture each Present. hVideo may be
 * NULL to use the current driver instance. Returns 0 on success.
 */
int SDL3GPUREND_MapScreenUpload(struct _VIDEO* hVideo, const void* bgra,
    int width, int height);

#ifdef __cplusplus
}
#endif

/*
 * Main entry point for device.
 */
#ifndef _NO_PROTOTYPES
struct br_device *BR_EXPORT BrDrv1SDL3GPURENDBegin(const char *arguments);
#endif /* _NO_PROTOTYPES */

#endif /* _BRSDL3GPUREND_H_ */
