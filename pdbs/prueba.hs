module Main where

import Data.List
import System.Environment

main :: IO ()
main = do
    list <- readRanks
    let nubbed = nub list
    if length nubbed == length list
        then putStr "si"
        else putStr $ "diferentes, nubbed " ++ show (length nubbed) ++ ". y list " ++ show (length list)

readRanks :: IO [String]
readRanks = do
    string <- readFile "../pdbs/cPDB.txt"
    return $ concat $ map (tail . words) $ lines string
