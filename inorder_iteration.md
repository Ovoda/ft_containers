
operator++ {
    
    1 if left leaf or if right child doesn't exist go up, return value

    2 if right child exist, go right and if not leaf go full left. return value

    3 if right leaf != end go up until becoming left child, there go up once. return value
}

operator-- {

    1 if right leaf or if left child doesn't exist, go up. return value
    
    2 if left child exist, go left and if not leaf go full right. return value

    3 if left leaf != begin, go up until becoming right child, there go up once. return value
}
