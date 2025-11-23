#include <QApplication>
#include "BiologistWindow.h"
#include "Service.h"
#include "Repository.h"

int main(int argc, char *argv[]) {
 QApplication a(argc, argv);

 Repository repo("biologists.txt", "bacteriums.txt");
 Service service(repo);

 ///WIndow for each biologist
 vector<BiologistWindow*> windows;
 for (const auto& biologist : service.getAllBiologists()) {
  auto* window = new BiologistWindow(service, biologist);
  service.addObserver(window);
  windows.push_back(window);
  window->show();
 }

 int result = a.exec();

 ///Save the date when closed
 service.saveToFile();

 // curatare windw
 for (auto* window : windows) {
  delete window;
 }

 return result;
}

