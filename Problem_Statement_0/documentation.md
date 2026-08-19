# 📝 Solution Documentation 
---

## Problem Understanding
**What the problem demanded:** The problem required building an interactive CUI-based Smart Cargo Terminal Management System to analyze shipment container loads, verify total weights against port capacity limits, and perform key management operations like sorting, searching, and exporting summary reports.

**Key concepts involved:**
- Custom Merge Sort Algorithm
- Using the Standard Template Library for features like vector and map
- File I/O stream operations 
- Dynamic terminal data visualization using * for bar charts

**My approach:**
- **Modular Data Processing:** I thought of creating a repeating menu based system supporting dual input modes—manual interactive entry or batch file parsing.
- **Analytics & Validation:** Processed container metrics (sum, min, max, average) dynamically and performed immediate threshold checks against specified port storage capacities.
- **Secondary Operations Subsystem:** Provided post-analysis options for customized data viewing, order statistics (Kth heaviest), lookups via mapping, and local text export.

---

## Conceptual Learning

### **New Concepts I Discovered**
- **File I/O Stuff** Before attempting this project, I had zero idea on how to do File Handling and this project gave me the chance to Explore File I/O.Learnt how to use the `<fstream>` library and how to read and save files.

### **How I Applied These Concepts**
- Implemented `merge_sort()` to arrange container weights in ascending order efficiently for both report generation and identifying the $K$-th heaviest container.
- Stored inputs in `std::multimap<int, int>` mapping weight $\rightarrow$ original container ID, enabling prompt retrieval when searching for container indices by weight.
- Leveraged C++ file streams (`ifstream` / `ofstream`) to parse raw shipment lists from external files and persist summary reports to local disk.

### **Potential Real-World Connections**
This project models real-world Logistics & Supply Chain Management systems used at shipping ports, freight terminals, and fulfillment hubs. Algorithms like merge sorting and mapped lookup structures directly mirror real-time port capacity management, automated crane routing, and container inventory indexing systems.
### 
**An useless line from the Creator** This was one of my first attempts in creating something "real", so some bugs and glitches might have creeped in. A feedback on how I can improve would be really appreciated..
