﻿#pragma once

// Задание 2

// Написать игру «Крестики - нолики»,
// учитывая следующие требования :
// - игровое поле размером 3×3 
// - должно состоять из кнопок;
// - при нажатии на кнопку,
// на ней должна отобразиться картинка(крестик или нолик).
// Для установки изображения на кнопку ей нужно 
// - отправить сообщение BM_SETIMAGE,
// - с которым в WPARAM передать значение IMAGE_BITMAP,
// - а в LPARAM — дескриптор растрового битового образа
// - (и главное не забыть про свойство Bitmap!!!);
// - необходимо предотвращать попытку поставить крестик 
// или нолик на занятую клетку;
// - предоставить пользователю право выбора первого
// хода,
// - используя флажок;
// - предусмотреть возможность выбора уровня сложности, 
// - используя переключатели;
// - предусмотреть кнопку «Начать новую игру».


#include <windows.h>
#include <time.h>
#include "resource.h"

enum {eComp, eUser} ePlayer;
enum {eRound, eCross} eFigure;

enum {eWalkComp, eWalkUser} eNowWalks;