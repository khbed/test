#pragma once
#ifndef UTILITY
#define UTILITY

#include "SFML/Graphics.hpp"
#include "constants.h"
#include <memory>
#include <iostream>

void drawShapes(sf::RenderWindow& window, std::vector<std::shared_ptr<sf::Drawable>> shapes) {
	for (auto shape : shapes) {
		window.draw(*shape);
	}
}

sf::RectangleShape drawTile(int x, int y, sf::Color color) {
	sf::RectangleShape tile(sf::Vector2f(TILE_LENGTH, TILE_LENGTH));
	tile.setPosition(sf::Vector2f(x * TILE_LENGTH, y * TILE_LENGTH));
	tile.setFillColor(color);
	return tile;
}

bool initializeTextures() {
	for (int i = 0; i < 12; i++) {
		Pieces piece = Pieces(i);
		PIECE_TEXTURES.at(piece).setSmooth(true);
		if (!PIECE_TEXTURES.at(piece).loadFromFile(PIECES_FOLDER + PIECE_TEXTURES_FILES.at(piece))) return false;
	}

	if (!FONT.loadFromFile(FONT_FILE)) return false;
	if (!MOVE_SOUND.loadFromFile(MOVE_SOUND_FILE)) return false;
	sound.setBuffer(MOVE_SOUND);
	sound.setVolume(35.f);

	return true;
}

sf::Vector2i getBoardPos(sf::Vector2i mousePos) {
	if (mousePos.x < 0 || mousePos.y < 0 || mousePos.x > BOARD_SIZE * TILE_LENGTH || mousePos.y > BOARD_SIZE * TILE_LENGTH) return sf::Vector2i(-1, -1);
	int x = (mousePos.x - (mousePos.x % (int)TILE_LENGTH))/TILE_LENGTH;
	int y = (mousePos.y - (mousePos.y % (int)TILE_LENGTH))/TILE_LENGTH;
	return sf::Vector2i(x, y);
}

bool isWhite(const Pieces& piece) {
	return (piece >= Pieces(6) && piece < Pieces(12));
}

bool isBlack(const Pieces& piece) {
	return (piece >= Pieces(0) && piece < Pieces(6));
}

Pieces getTile(sf::Vector2i position) {
	return board[position.x][position.y];
}

bool isInBoard(sf::Vector2i position) {
	if (position.x >= BOARD_SIZE) return false;
	if (position.x < 0) return false;
	if (position.y >= BOARD_SIZE) return false;
	if (position.y < 0) return false;
	return true;
}

std::vector<sf::Vector2i> getPawnMoves(Tile tile) {
	std::vector<sf::Vector2i> moves;
	if (isWhite(tile.piece)) {
		if (getTile(tile.position + sf::Vector2i(0, -1)) == Pieces::Empty) {
			moves.push_back(tile.position + sf::Vector2i(0, -1));
			if (tile.position.y == 6) {
				if (getTile(tile.position + sf::Vector2i(0, -2)) == Pieces::Empty) {
					moves.push_back(tile.position + sf::Vector2i(0, -2));
				}
			}
		}
		if (tile.position.x > 0) {
			if (isBlack(getTile(tile.position + sf::Vector2i(-1, -1)))) {
				moves.push_back(tile.position + sf::Vector2i(-1, -1));
			}
		}
		if (tile.position.x < 7) {
			if (isBlack(getTile(tile.position + sf::Vector2i(1, -1)))) {
				moves.push_back(tile.position + sf::Vector2i(1, -1));
			}
		}
	}
	else {
		if (getTile(tile.position + sf::Vector2i(0, 1)) == Pieces::Empty) {
			moves.push_back(tile.position + sf::Vector2i(0, 1));
			if (tile.position.y == 1) {
				if (getTile(tile.position + sf::Vector2i(0, 2)) == Pieces::Empty) {
					moves.push_back(tile.position + sf::Vector2i(0, 2));
				}
			}
		}
		if (tile.position.x > 0) {
			if (isWhite(getTile(tile.position + sf::Vector2i(-1, 1)))) {
				moves.push_back(tile.position + sf::Vector2i(-1, 1));
			}
		}
		if (tile.position.x < 7) {
			if (isWhite(getTile(tile.position + sf::Vector2i(1, 1)))) {
				moves.push_back(tile.position + sf::Vector2i(1, 1));
			}
		}
	}
	return moves;
}

std::vector<sf::Vector2i> getKnightMoves(Tile tile) {
	std::vector<sf::Vector2i> moves;
	const sf::Vector2i POS = tile.position;

	std::vector<sf::Vector2i> shifts = { sf::Vector2i(2, 1), sf::Vector2i(-2, 1), sf::Vector2i(2, -1), sf::Vector2i(-2, -1), sf::Vector2i(1, 2), sf::Vector2i(1, -2), sf::Vector2i(-1, 2), sf::Vector2i(-1, -2) };

	for (auto shift : shifts) {
		if (isInBoard(POS + shift)) {
			if (getTile(POS + shift) == Pieces::Empty) {
				moves.push_back(POS + shift);
			}
			else if (isWhite(tile.piece)) {
				if (isBlack(getTile(POS + shift))) {
					moves.push_back(POS + shift);
				}
			}
			else if (isBlack(tile.piece)) {
				if (isWhite(getTile(POS + shift))) {
					moves.push_back(POS + shift);
				}
			}
		}
	}
	return moves;
}

std::vector<sf::Vector2i> getRookMoves(Tile tile) {
	std::vector<sf::Vector2i> moves;
	const sf::Vector2i POS = tile.position;

	std::vector<sf::Vector2i> directions = { sf::Vector2i(0, 1), sf::Vector2i(0, -1), sf::Vector2i(1, 0), sf::Vector2i(-1, 0) };

	for (auto direction : directions) {
		bool blocked = false;
		int shift = 0;
		while (!blocked) {
			shift++;
			if (isInBoard(POS + shift * direction)) {
				Pieces target = getTile(POS + shift * direction);
				if (target == Pieces::Empty) {
					moves.push_back(POS + shift * direction);
				}
				else if (isWhite(tile.piece)) {
					if (isBlack(getTile(POS + shift * direction))) {
						moves.push_back(POS + shift * direction);
					}
					blocked = true;
				}
				else if (isBlack(tile.piece)) {
					if (isWhite(getTile(POS + shift * direction))) {
						moves.push_back(POS + shift * direction);
					}
					blocked = true;
				}
			}
			else {
				blocked = true;
			}
		}
	}
	return moves;
}

std::vector<sf::Vector2i> getBishopMoves(Tile tile) {
	std::vector<sf::Vector2i> moves;
	const sf::Vector2i POS = tile.position;

	std::vector<sf::Vector2i> directions = { sf::Vector2i(1, 1), sf::Vector2i(1, -1), sf::Vector2i(-1, 1), sf::Vector2i(-1, -1) };

	for (auto direction : directions) {
		bool blocked = false;
		int shift = 0;
		while (!blocked) {
			shift++;
			if (isInBoard(POS + shift * direction)) {
				Pieces target = getTile(POS + shift * direction);
				if (target == Pieces::Empty) {
					moves.push_back(POS + shift * direction);
				}
				else if (isWhite(tile.piece)) {
					if (isBlack(getTile(POS + shift * direction))) {
						moves.push_back(POS + shift * direction);
					}
					blocked = true;
				}
				else if (isBlack(tile.piece)) {
					if (isWhite(getTile(POS + shift * direction))) {
						moves.push_back(POS + shift * direction);
					}
					blocked = true;
				}
			}
			else {
				blocked = true;
			}
		}
	}
	return moves;
}

std::vector<sf::Vector2i> getKingMoves(Tile tile) {
	std::vector<sf::Vector2i> moves;
	const sf::Vector2i POS = tile.position;

	std::vector<sf::Vector2i> shifts = { sf::Vector2i(0, 1), sf::Vector2i(0, -1), sf::Vector2i(1, 0), sf::Vector2i(-1, 0), sf::Vector2i(1, 1), sf::Vector2i(1, -1), sf::Vector2i(-1, 1), sf::Vector2i(-1, -1) };

	for (auto shift : shifts) {
		if (isInBoard(POS + shift)) {
			if (getTile(POS + shift) == Pieces::Empty) {
				moves.push_back(POS + shift);
			}
			else if (isWhite(tile.piece)) {
				if (isBlack(getTile(POS + shift))) {
					moves.push_back(POS + shift);
				}
			}
			else if (isBlack(tile.piece)) {
				if (isWhite(getTile(POS + shift))) {
					moves.push_back(POS + shift);
				}
			}
		}
	}
	return moves;
}

std::vector<sf::Vector2i> getPossibleMoves(const Tile& tile) {
	std::vector<sf::Vector2i> moves;
	if (!isWhite(tile.piece) && !isBlack(tile.piece)) return moves;

	PieceTypes type = PIECES_TYPES.at(tile.piece);
	std::vector<sf::Vector2i> diagonalMoves;
	
	switch (type) {
	case PieceTypes::King:
		moves = getKingMoves(tile);
		break;
	case PieceTypes::Knight:
		moves = getKnightMoves(tile);
		break;
	case PieceTypes::Rook:
		moves = getRookMoves(tile);
		break;
	case PieceTypes::Bishop:
		moves = getBishopMoves(tile);
		break;
	case PieceTypes::Queen:
		moves = getRookMoves(tile);
		diagonalMoves = getBishopMoves(tile);
		for (auto diagMove : diagonalMoves) {
			bool exists = false;
			for (auto move : moves) {
				if (diagMove == move) exists = true;
			}
			if (!exists) moves.push_back(diagMove);
		}

		break;
	case PieceTypes::Pawn:
		moves = getPawnMoves(tile);
		break;
	default: 
		break;
	}
	return moves;
}
#endif // !UTILITY
