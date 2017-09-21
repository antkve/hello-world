worldList = 
    [((0, 0), 1), ((0, 1), 1),((0, 2), 1), ((0, 3), 1), ((0, 4), 0), ((0, 5), 0), ((0, 6), 0), ((0, 7), 0), ((0, 8), 0), ((0, 9), 1),
     ((1, 0), 1), ((1, 1), 0),((1, 2), 0), ((1, 3), 0), ((1, 4), 0), ((1, 5), 0), ((1, 6), 0), ((1, 7), 0), ((1, 8), 0), ((1, 9), 1),
     ((2, 0), 1), ((2, 1), 0),((2, 2), 0), ((2, 3), 0), ((2, 4), 0), ((2, 5), 0), ((2, 6), 0), ((2, 7), 0), ((2, 8), 0), ((2, 9), 1),
     ((3, 0), 1), ((3, 1), 0),((3, 2), 0), ((3, 3), 0), ((3, 4), 0), ((3, 5), 0), ((3, 6), 0), ((3, 7), 0), ((3, 8), 0), ((3, 9), 1),
     ((4, 0), 1), ((4, 1), 1),((4, 2), 1), ((4, 3), 1), ((4, 4), 1), ((4, 5), 1), ((4, 6), 1), ((4, 7), 1), ((4, 8), 1), ((4, 9), 1)]

doit  = search ((0, 0), (4, 9)) [] (getallthatare (==1) worldList)
getallthatare f xyss = map fst $ filter ( f . snd ) xyss
surrounding8of (x, y) = [(x1, y1) | x1 <- [x-1..x+1], y1 <- [y-1..y+1]]
intisinbounds ((lowx, lowy), (highx, highy)) (x, y) = x `elem` [lowx..highx] && y `elem` [lowy..highy]
newandinbounds xs queue searched mapBounds = filter (intisinbounds mapBounds) $ filter (not . flip elem (queue ++ searched)) xs
search mapBounds searched [centre] = centre
search mapBounds searched (centre:queue) = search mapBounds (centre:searched) 
                                                                                   $ queue ++ newandinbounds (surrounding8of centre) queue (centre:searched) mapBounds
