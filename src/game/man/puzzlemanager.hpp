#pragma once
// puzzle
#include <game/man/puzzle/puzzle.hpp>
// cmp
#include <ecs/cmp/component.hpp>
// utils
#include <ecs/util/globals.hpp>
// libs
#include <iostream>
#include <cstdlib>
#include <memory>
#include <unordered_map>
#include <vector>

struct PuzzleManager : ECS::SingletonComponent
{
    using PuzzleName     = ECS::PUZZLE_TYPE;

    using PuzzleMap = std::unordered_map<PuzzleName, std::unique_ptr<Puzzle>>;

    explicit PuzzleManager() : ECS::SingletonComponent(ECS::IDSingleCMPPuzzleM){}

    // añadir un nuevo puzzle
    template <typename PuzzleType>
    void addPuzzle(ECS::PUZZLE_TYPE type, PuzzleType puzzle)
    {                 
        puzzleMap.emplace(type, std::make_unique<PuzzleType>(std::move(puzzle)));
    }

    void erasePuzzle(ECS::PUZZLE_TYPE type)
    {                 
        auto it = puzzleMap.find(type);
        if (it != puzzleMap.end())
        {
            puzzleMap.erase(it->first);
        }
    }

    // por ser singletonComponent
    static std::size_t getSingletonComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(ECS::IDSingleCMPPuzzleM);
    }

    // obtener todo el map de puzzles
    PuzzleMap &getAllPuzzles()
    {
        return puzzleMap;
    }

    Puzzle *getPuzzle(ECS::PUZZLE_TYPE type)
    {
        Puzzle* puzzle_aux{ nullptr };
        auto it = puzzleMap.find(type);
        if (!puzzleMap.empty() && it != puzzleMap.end())
        {
            puzzle_aux = it->second.get();
        }
        return puzzle_aux;
    }

    // limpiar todos los datos de los puzzles
    void clearAllPuzzles() noexcept
    {
        puzzleMap.clear();
    }

    // // recorrer el vector de componentes
    [[nodiscard]] auto begin() noexcept { return puzzleMap.begin(); }
    [[nodiscard]] auto end()   noexcept { return puzzleMap.end(); }

private:
    PuzzleMap puzzleMap{};
};