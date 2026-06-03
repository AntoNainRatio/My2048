# My2048 - Bot with Expectimax Algorithm

An implementation of the 2048 game in C with a **GTK+3 graphical interface** and an **intelligent bot** using the **multi-threaded expectimax algorithm** to play automatically.

---

## Table of Contents

- [Features](#features)
- [Expectimax Algorithm](#expectimax-algorithm)
- [Installation](#installation)
- [Compilation](#compilation)
- [Usage](#usage)

---

## Features

### Classic 2048 Game
- 4×4 board with standard 2048 mechanics
- Random tile spawning (90% → 2, 10% → 4)

### Graphical Interface
- Smooth and responsive GTK+3 interface
- Manual mode: play with keyboard arrows

### Intelligent Bot
- **Expectimax Algorithm**: Makes optimal decisions
- **Multi-threading**: Evaluates 4 directions in parallel (4x faster)
- **Deep Search**: Evaluates up to 4 moves ahead

You can modify the depth of the search via DEPTH_MAX in `/src/bot.c`.

---

## Expectimax Algorithm

### Overview

The **Expectimax** algorithm is a variant of minimax that handles **uncertainty** (random tile spawning). It's perfect for 2048!

### Main Idea

For each position, we calculate a **score** by:

1. **Testing each possible move** (UP, DOWN, LEFT, RIGHT)
2. **Predicting where new tiles will appear** (probabilities: 90% → 2, 10% → 4)
3. **Recursively evaluating** each future scenario
4. **Choosing the move with the best expected score**

### Mathematical Formula

```
Score(position) = Max over all moves of:
    ∑ (spawn probability) × Score(position after spawn)

where:
- 90% chance a 2 will appear
- 10% chance a 4 will appear
```

### Pseudo-code

```
function expectimax(board, depth):
    if depth == 0:
        return evaluatePosition(board)
    
    bestScore = -∞
    
    for each direction in [UP, DOWN, LEFT, RIGHT]:
        if direction is valid:
            newBoard = board after movement
            
            score = 0
            for each empty cell in newBoard:
                // Spawn a 2 (90%)
                boardWith2 = copy of newBoard with 2 at cell
                score += 0.9 × expectimax(boardWith2, depth-1)
                
                // Spawn a 4 (10%)
                boardWith4 = copy of newBoard with 4 at cell
                score += 0.1 × expectimax(boardWith4, depth-1)
            
            bestScore = max(bestScore, score)
    
    return bestScore
```

### Scoring Heuristics

The position score combines **4 spatial heuristics**:

1. **Bottom-Left**: Prefers large tiles in bottom-left
2. **Bottom-Right**: Prefers large tiles in bottom-right
3. **Top-Right**: Prefers large tiles in top-right
4. **Top-Left**: Prefers large tiles in top-left

The **average** of these 4 heuristics provides a robust score.

### Example: Depth 1

```
Initial position
    ↓
├─ Test UP → calculate impact of all possible spawns
├─ Test DOWN → calculate impact of all possible spawns
├─ Test LEFT → calculate impact of all possible spawns
└─ Test RIGHT → calculate impact of all possible spawns
    ↓
Choose the move with the best average score
```

---

## Installation

### Install Dependencies (Ubuntu/Debian)

```bash
sudo apt-get update && sudo apt-get install -y \
    build-essential \
    make \
    gcc \
    libgtk-3-dev \
    pkg-config
```

### Install Dependencies (Fedora/RHEL)

```bash
sudo dnf install -y gcc make gtk3-devel pkg-config
```

### Install Dependencies (Arch)

```bash
sudo pacman -S base-devel gtk3 pkg-config
```

---

## Compilation

### 1. Clone the Project

```bash
git clone git@github.com:AntoNainRatio/My2048.git
cd my2048
```

### 2. Compile

```bash
make clean
make
```

**Result**: An executable `my2048` is created in the current directory.

### Verify Compilation

```bash
ls -la my2048
```

---

## Usage

### Manual Mode (Play with Keyboard)

```bash
./my2048
```

**Controls**:
- ↑ **Up Arrow**: Move tiles up
- ↓ **Down Arrow**: Move tiles down
- ← **Left Arrow**: Move tiles left
- → **Right Arrow**: Move tiles right

### Automatic Bot Mode

```bash
./my2048 --bot
```

The bot plays **automatically** using the expectimax algorithm. Watch how it optimizes the position!

### Help

```bash
./my2048 --help
```

---

**Made by: AntoNainRatio**
