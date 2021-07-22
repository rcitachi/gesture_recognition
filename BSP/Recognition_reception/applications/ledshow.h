/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-21     years       the first version
 */
#ifndef APPLICATIONS_LEDSHOW_H_
#define APPLICATIONS_LCDSHOW_H_

#define LED_PIN GET_PIN(I, 8)

void ledoff(void);
void ledon(void);
void ledshow_1(void);

void ledshow_2(void);
#endif /* APPLICATIONS_LEDSHOW_H_ */
