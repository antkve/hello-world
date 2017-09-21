nemo worldList  = search ((0, 0), (4, 9)) [] (getallthatare (=='#') worldList)
getallthatare f xyss = map fst $ filter ( f . snd ) xyss
surrounding8of (x, y) = [(x1, y1) | x1 <- [x-1..x+1], y1 <- [y-1..y+1]]
intisinbounds ((lowx, lowy), (highx, highy)) (x, y) = x `elem` [lowx..highx] && y `elem` [lowy..highy]
newandinbounds xs queue searched mapBounds = filter (intisinbounds mapBounds) $ filter (not . flip elem (queue ++ searched)) xs
search mapBounds searched [centre] = centre
search mapBounds searched (centre:queue) = search mapBounds (centre:searched) 
                $ queue ++ newandinbounds (surrounding8of centre) queue (centre:searched) mapBounds
