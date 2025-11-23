# Bacteria Research Manager 🔬

A sophisticated desktop application developed in **C++** using the **Qt 6 Framework**. This project simulates a biological research environment where multiple biologists can manage bacterial cultures and diseases simultaneously.

It demonstrates advanced GUI techniques including **Model/View Architecture**, **Custom Painting**, and the **Observer Design Pattern** for real-time synchronization across multiple windows.

## 🚀 Key Technical Features

* **Qt Model/View Architecture:** Implemented a custom `QAbstractTableModel` (`BacteriumTableModel`) to display complex data in tabular format efficiently. This allows for sorting and filtering directly within the view logic.
* **Observer Design Pattern:** The application supports multiple concurrent windows (simulating different biologists). When one user adds a bacterium or disease, all other open windows update instantly without manual refreshing.
* **Custom 2D Graphics:** Includes a `SpeciesVisualizer` using `QPainter` to render geometric representations of bacteria populations based on real-time data attributes.
* **Layered Architecture:**
    * **Domain:** `Bacterium`, `Biologist` entities.
    * **Repository:** Handles data persistence (reading/writing to text files).
    * **Service:** Business logic and coordination between the repository and GUI.
    * **GUI:** Custom Windows and Visualization widgets.

## 📸 Functionality

1.  **Multi-Window Sync:** Changes made in the "Alex" window are immediately reflected in the "Tudor" window.
2.  **Data Management:** Add bacteria and associated diseases.
3.  **Filtering:** Filter table data by species type using a ComboBox.
4.  **Visualization:** A dedicated view (`SpeciesVisualizer`) draws shapes representing the bacteria count and types.

## 📂 Project Structure

```text
├── domain/       # Bacterium, Biologist classes
├── repository/   # File handling logic
├── service/      # Controller logic
├── models/       # Custom QAbstractTableModel implementation
├── gui/          # BiologistWindow and SpeciesVisualizer
└── observer/     # Observer interface
