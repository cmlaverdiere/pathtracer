#include <iostream>
#include <string>
#include <vector>

#include "frontends.hpp"
#include "image.hpp"
#include "scene.hpp"

// TODO re-architect threading.
// std::vector<std::thread> threads;
// for (int i=0; i < m_render_opts.num_threads; i++) {
//     threads.push_back(
//             std::thread(&Renderer::render_pixels, this, std::ref(pixel_queue),
//                 std::ref(pixels), &sample_counts[0]));
// }
// for (std::thread &t : threads){
//     t.join();
// }

void ImageFrontend::render_image(RenderOpts render_opts, Scene &scene,
                                 std::string outfile_path) {
    Renderer renderer(render_opts);

    std::cout << "{0% " << std::string(render_opts.bar_length - 8, ' ') << " 100%}" << std::endl;
    std::cout << "{" << std::flush;
    auto start = std::chrono::steady_clock::now();

    std::vector<vec3f> *pixels = renderer.get_pixels();

    int pixels_done = 0;
    const int total_needed = renderer.m_render_opts.image_width
        * renderer.m_render_opts.image_height
        * renderer.m_render_opts.num_samples;

    while (pixels_done < total_needed) {
        renderer.shade_next_pixel(scene);
        pixels_done++;

        if ((pixels_done % (total_needed / render_opts.bar_length)) == 0) {
            std::cout << "." << std::flush;
        }
    }

    auto end = std::chrono::steady_clock::now();

    std::cout << "}" << std::endl;
    std::cout << "Traced image in " <<
        (std::chrono::duration_cast<std::chrono::milliseconds>
         (end - start).count() / 1000.0) << " seconds." << std::endl;

    std::cout << "Saving image to " << outfile_path << std::endl;
    write_png(outfile_path.c_str(), *pixels,
              renderer.m_render_opts.image_width,
              renderer.m_render_opts.image_height);
}

// TODO
void OpenGLFrontend::render_scene(RenderOpts render_opts, Scene &scene) {
    Renderer renderer(render_opts);
}
