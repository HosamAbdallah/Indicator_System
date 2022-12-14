/******************************************************************************/
/*                                                                            */
/* !Layer           : Application Layer (APP)                                 */
/*                                                                            */
/* !Component       : MODE                                                    */
/* !Description     : Initializes the MODE module                             */
/*                                                                            */
/* !Module          : MODE                                                    */
/* !Description     : MODE Module interface                                   */
/*                                                                            */
/* !File            : MODE_int.h                                              */
/*                                                                            */
/* !Scope           : Public                                                  */
/*                                                                            */
/* !Coding language : C                                                       */
/*                                                                            */
/* !Project         : Induction training exercise project                     */
/*                                                                            */
/* !Target          : PIC 16F877A                                             */
/*                                                                            */
/* !Compiler        : SDCC V3.5                                               */
/*                                                                            */
/* !COPYRIGHT 2015 Valeo Egypt                                                */
/*  all rights reserved                                                       */
/*                                                                            */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Hosam Abdallah                   !Date : OCT 31, 2022   */
/* !Coded by        : Hosam Abdallah                   !Date : OCT 31, 2022   */
/*                                                                            */
/* Rev 1.0   JULY 19, 2015     Initial release                                */
/******************************************************************************/

/******************************************************************************/
/*! \par
*   Interface of the module MODE. \n
*   This file contains the interface of the module MODE.                      */
/******************************************************************************/

#ifndef MODE_INT_H
#define MODE_INT_H

/******************************************************************************/
/******************************************************************************/
/****************************** Types Definition ******************************/
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/*! \Description Define MODE module States                                    */
/*! \Trace_To                                                                 */
/******************************************************************************/

typedef enum{
IDLE=0,
RIGHT_BLINK,
LEFT_BLINK,
HAZZARD_BLINK,
STATES_MAX_SIZE=4
}MODE_enutModeState;

/******************************************************************************/
/******************************************************************************/
/*************************** Functions Declaration ****************************/
/******************************************************************************/
/******************************************************************************/
extern void MODE_vidInit(void);
extern void MODE_vidTask(void);

#endif /* PBD_INT_H */







