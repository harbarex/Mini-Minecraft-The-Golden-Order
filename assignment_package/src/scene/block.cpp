#include "block.h"

/**
 * @brief createBlockFaces
 *  This creates an array of 6 BlockFaces of a cube.
 *  The input arguments are used for various kinds of blocks (textures)
 *  Note: arrange the vertices (v1 to v4) of each BlockFace in counter-clockwise manner.
 *  Note: Further helpers might be created to use different normals if needed.
 *  @param uvOffsets : array<glm::vec2, 6>
 *      The uv offsets of each face.
 *      Order: XPOS, XNEG, YPOS, YNEG, ZPOS, ZNEG
 * @return std::array<BlockFace, 6>
 */
std::array<BlockFace, 6> Block::createBlockFaces(std::array<glm::vec2, 6> uvOffsets)
{
    // each texture : 16 x 16
    float length = 1.f /16.f;
    return {
        BlockFace(XPOS, glm::vec4( 1,  0,  0, 0),
                  VertexData(glm::vec4(1, 0, 1, 1), uvOffsets[0]),
                  VertexData(glm::vec4(1, 0, 0, 1), uvOffsets[0] + glm::vec2(length, 0.)),
                  VertexData(glm::vec4(1, 1, 0, 1), uvOffsets[0] + glm::vec2(length, length)),
                  VertexData(glm::vec4(1, 1, 1, 1), uvOffsets[0] + glm::vec2(0, length))),
        BlockFace(XNEG, glm::vec4(-1,  0,  0, 0),
                  VertexData(glm::vec4(0, 0, 0, 1), uvOffsets[1]),
                  VertexData(glm::vec4(0, 0, 1, 1), uvOffsets[1] + glm::vec2(length, 0.)),
                  VertexData(glm::vec4(0, 1, 1, 1), uvOffsets[1] + glm::vec2(length, length)),
                  VertexData(glm::vec4(0, 1, 0, 1), uvOffsets[1] + glm::vec2(0, length))),
        BlockFace(YPOS, glm::vec4( 0,  1,  0, 0),
                  VertexData(glm::vec4(0, 1, 1, 1), uvOffsets[2]),
                  VertexData(glm::vec4(1, 1, 1, 1), uvOffsets[2] + glm::vec2(length, 0.)),
                  VertexData(glm::vec4(1, 1, 0, 1), uvOffsets[2] + glm::vec2(length, length)),
                  VertexData(glm::vec4(0, 1, 0, 1), uvOffsets[2] + glm::vec2(0, length))),
        BlockFace(YNEG, glm::vec4( 0, -1,  0, 0),
                  VertexData(glm::vec4(0, 0, 0, 1), uvOffsets[3]),
                  VertexData(glm::vec4(1, 0, 0, 1), uvOffsets[3] + glm::vec2(length, 0.)),
                  VertexData(glm::vec4(1, 0, 1, 1), uvOffsets[3] + glm::vec2(length, length)),
                  VertexData(glm::vec4(0, 0, 1, 1), uvOffsets[3] + glm::vec2(0, length))),
        BlockFace(ZPOS, glm::vec4( 0,  0,  1, 0),
                  VertexData(glm::vec4(0, 0, 1, 1), uvOffsets[4]),
                  VertexData(glm::vec4(1, 0, 1, 1), uvOffsets[4] + glm::vec2(length, 0.)),
                  VertexData(glm::vec4(1, 1, 1, 1), uvOffsets[4] + glm::vec2(length, length)),
                  VertexData(glm::vec4(0, 1, 1, 1), uvOffsets[4] + glm::vec2(0., length))),
        BlockFace(ZNEG, glm::vec4( 0,  0, -1, 0),
                  VertexData(glm::vec4(1, 0, 0, 1), uvOffsets[5]),
                  VertexData(glm::vec4(0, 0, 0, 1), uvOffsets[5] + glm::vec2(length, 0.)),
                  VertexData(glm::vec4(0, 1, 0, 1), uvOffsets[5] + glm::vec2(length, length)),
                  VertexData(glm::vec4(1, 1, 0, 1), uvOffsets[5] + glm::vec2(0., length)))
    };
};



/**
 * @brief createBlockFaces
 *  Create a default set of block faces (UVs should not be used in this case)
 * @return
 */
std::array<BlockFace, 6> Block::createBlockFaces()
{
    return createBlockFaces({glm::vec2(0.f), glm::vec2(0.f),
                             glm::vec2(0.f), glm::vec2(0.f),
                             glm::vec2(0.f), glm::vec2(0.f)});
};


/**
 * @brief Block::isOpaque
 *  The helper function to determine whether a given block type is
 *  treated as opaque or not.
 * @return
 */
bool Block::isOpaque(BlockType type)
{
    return (transparentBlockTypes.find(type) == transparentBlockTypes.end());
}


/**
 * @brief Block::isTransparent
 *  The helper function to determine whether a given block type
 *  is treated as transparent or not
 * @param type
 * @return
 */
bool Block::isTransparent(BlockType type)
{
    return (transparentBlockTypes.find(type) != transparentBlockTypes.end());
}

bool Block::isLiquid(BlockType type)
{
    return (liquidBlockTypes.find(type) != liquidBlockTypes.end());
}

/**
 * @brief Block::isAnimatable
 *  The helper function to determine whether a given block type
 *  is animatable or not
 * @param type
 * @return
 */
bool Block::isAnimatable(BlockType type)
{
    return (animatableBlockTypes.find(type) != animatableBlockTypes.end());
}

/**
 * @brief Block::getAnimatableFlag
 *  Get the predefined animatable flag depending on the block type
 *  Use vector for convenience in passing data to GPU
 * @return float, vec2(1) is animatable block, vec2(-1) is non-animatable block
 */
glm::vec2 Block::getAnimatableFlag(BlockType type)
{
    if (isAnimatable(type)) {
        return glm::vec2(1.f);
    }

    return glm::vec2(-1.f);
}

/**
 * @brief Block::isEmpty
 *  The helper function to determine whether a given block type
 *  is treated as empty or not.
 *  It is used for drawing faces of transparent block
 * @param type
 * @return
 */
bool Block::isEmpty(BlockType type)
{
    return (type == EMPTY);
}


/**
 * @brief Block::getColors
 *  Get the predefined color depending on the block type
 * @return glm::vec4, rgba
 */
glm::vec4 Block::getColors(BlockType type)
{
    glm::vec4 color = glm::vec4();

    switch (type) {
    case GRASS:
        color = glm::vec4(95.f, 159.f, 53.f, 255.f) / 255.f;
        break;
    case DIRT:
        color =  glm::vec4(121.f, 85.f, 58.f, 255.f) / 255.f;
        break;
    case STONE:
        color =  glm::vec4(0.5f, 0.5f, 0.5f, 1.f);
        break;
    case WATER:
        color = glm::vec4(0.f, 0.f, 0.75f, 1.f);
        break;
    case SNOW:
        color = glm::vec4(1.f, 1.f, 1.f, 1.f);
        break;
    default:
        // Other block types are not yet handled, so we default to debug purple
        color = glm::vec4(1.f, 0.f, 1.f, 1.f);
        break;
    }

    return color;
}

void Block::insertNewUVCoord(BlockType blockType, std::array<glm::vec2, 6> uv) {
    BlockCollection[blockType] = Block::createBlockFaces(uv);
}

void Block::loadUVCoordFromText(const char* img_path) {
    // read text file
    QFile f(img_path);
    f.open(QIODevice::ReadOnly);
    QTextStream s(&f);
    QString line;
    bool readCoord = false;
    int coordCount = 0;
    std::array<glm::vec2, 6> uvOffsets;
    BlockType currBlockType;

    while (!s.atEnd()) {
        line = s.readLine();
        if (line.size() == 0 || line.startsWith("#")) {
            // skip empty line and line starts with #
            continue;
        }

        if (readCoord) {
            // store uv coordinate into temp array
            uvOffsets[coordCount] = glm::vec2(line.split(" ")[0].toDouble(), line.split(" ")[1].toDouble());
            coordCount += 1;
        } else if (blockTypeMap.find(line.toStdString()) != blockTypeMap.end()) {
            // identify which block
            currBlockType = blockTypeMap[line.toStdString()];
            readCoord = true;
        }

        if (coordCount == 6) {
            // store 6 uv coordinates into BlockCollection

            insertNewUVCoord(currBlockType, uvOffsets);
            uvOffsets.empty();
            coordCount = 0;
            readCoord = false;
        }
    }
}


/**
 * Instantiate various kinds of blocks here.
 * TODO: Update uvs for each block.
 * Access to this static variable with Block::BlockCollection
 **/
std::unordered_map<BlockType, std::array<BlockFace, 6>> Block::BlockCollection = {
    {}
};

std::unordered_map<std::string, BlockType> Block::blockTypeMap = {
    {{"GRASS", GRASS},
    {"DIRT", DIRT},
    {"STONE", STONE},
    {"WATER", WATER},
    {"SNOW", SNOW},
    {"LAVA", LAVA},
    {"BEDROCK", BEDROCK},
    {"ICE", ICE},
    {"WOOD", WOOD},
    {"LEAF", LEAF}}
};

std::unordered_set<BlockType> Block::transparentBlockTypes = {
    EMPTY, WATER, ICE
};

std::unordered_set<BlockType> Block::animatableBlockTypes = {
    WATER, LAVA
};

std::unordered_set<BlockType> Block::liquidBlockTypes = {
    WATER, LAVA
};
