# Astryx Engine Documentation

Welcome to the Astryx Engine Documentation! 

> **Note:** I will try my best to keep this up to date, but please forgive me if certain parts lag behind development. If you spot something outdated, feel free to reach out or open an issue, and I will update it as soon as possible!

---

### Documentation Directory Structure
This folder serves as the central hub for understanding, extending, and writing code for the Astryx Engine.

```text
docs/
├── architecture/         # High-level design overviews and systems flow
├── explanations/         # Conceptual guides and graphics theory
├── CODING_STANDARDS.md   # Naming conventions, style guides, and formatting
└── CONTRIBUTING.md       # How to report bugs, suggest features, and submit PRs
```

#### 📁 architecture/
The architecture/ folder provides a high-level design overview of how our engine flows and how systems are structured. It assumes you understand core graphics concepts (like the standard OpenGL pipeline) and want to see how Astryx specifically implements them. It is meant to give you a structural blueprint so you can safely jump in and add new features.

#### 📁 explanations/
The explanations/ folder is dedicated to teaching the underlying concepts behind each section of the engine. If you aren't yet familiar with a specific topic (e.g., how a specific rendering technique works conceptually outside of code), look here first. Currently, this folder focuses entirely on rendering, but it will expand to include physics, audio, and scripting as the roadmap progresses.

#### Contribution & Standards
Before writing any code, please review our core reference documents to keep the codebase clean and unified:

1. Read our Coding Standards to align your code style with the project requirements.

2. Check out the Contributing Guidelines for details on our branching model and pull request process.