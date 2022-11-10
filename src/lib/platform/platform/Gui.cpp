#include "Gui.h"
#include <tuple>

#if defined(_WIN32)
#include <windows.h>
#elif defined(PLATFORM_GTK_DIALOG)
#include <gtk/gtk.h>
#else
#include <iostream>
#endif

namespace ad {
namespace platform {


#if defined(_WIN32)

void showErrorBox(const std::string & aMessage, const std::string & aTitle)
{
    MessageBox(nullptr,
               aMessage.c_str(),
               aTitle.empty() ? nullptr : aTitle.c_str(),
               MB_OK | MB_ICONERROR);
}

#elif defined(PLATFORM_GTK_DIALOG)
void activate(GtkApplication* aApp, gpointer aUserData)
{
    auto [aMessage, aTitle] = *reinterpret_cast<std::tuple<const std::string &, const std::string &>*>(aUserData);
    GtkWidget * dialog = gtk_application_window_new(aApp);
    gtk_window_set_title(GTK_WINDOW(dialog), aTitle.c_str());
    gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);
    GtkWidget * label = gtk_label_new(aMessage.c_str());
    gtk_label_set_line_wrap(GTK_LABEL(label), true);
    gtk_label_set_max_width_chars(GTK_LABEL(label), 30);
    gtk_widget_set_size_request(GTK_WIDGET(label), 400, 200);
    gtk_container_add(GTK_CONTAINER(dialog), label);
    gtk_widget_show_all(dialog);
}

void showErrorBox(const std::string & aMessage, const std::string & aTitle)
{
    GtkApplication * app = gtk_application_new(nullptr, G_APPLICATION_DEFAULT_FLAGS);
    auto data = std::tie(aMessage, aTitle);
    g_signal_connect(app, "activate", G_CALLBACK(activate), &data);
    int status = g_application_run(G_APPLICATION(app), 0, nullptr);
    g_object_unref(app);
}
#else

// TODO Ad 2022/02/22: Implement for other platforms.
void showErrorBox(const std::string & aMessage, const std::string & aTitle)
{
    std::cerr 
        << (aTitle.empty() ? "Error: " : aTitle + ": ")
        << aMessage 
        << "\n"
        ;
}

#endif


} // namespace platform
} // namespace ad
