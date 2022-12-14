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
*   Configuration of the module MODE. \n
*   This file contains the internal configurations of the module MODE.        */
/******************************************************************************/


#include "tif_int.h"
#include "hif_int.h"
#include "pbd_int.h"

/******************************************************************************/

/*! Include the turn interface header                                         */
/*! \Trace_To																  */
#include "tif_int.h"

/*! Include the hazzard interface header                                      */
/*! \Trace_To                                                                 */
#include "hif_int.h"

/*! Include the push button driver header                                     */
/*! \Trace_To                                                                 */
#include "pbd_int.h"

/*! Include the push button types header                                      */
/*! \Trace_To                                                                 */
#include "pbd_types.h"

/******************************************************************************/

/******************************************************************************/
/************************** Private Global Variables **************************/
/******************************************************************************/
static MODE_enutModeState enutModeState=IDLE;
static MODE_enutModeState enutModeStatePervious=IDLE;

/******************************************************************************/
/*! \Description Initialize the MODE driver variables                         */
/*! \return      None                                                         */
/*! \Trace_To                                                                 */
/******************************************************************************/

void MODE_vidInit(void)
{
    enutModeState=IDLE;
    HIF_vidSetMode(HIF_UNDEFINED_MODE);
    TIF_vidSetMode(TIF_UNDEFINED_MODE);
}

void MODE_vidTask(void)
{
    uint8 u8Hazzard=PBD_enuGetButtonState(PBD_BUTTON_HAZZARD);
    uint8 u8StepUp=PBD_enuGetButtonState(PBD_BUTTON_STEP_UP);
    uint8 u8StepDown=PBD_enuGetButtonState(PBD_BUTTON_STEP_DOWN);

    /*  Switch cases on current state */
    switch(enutModeState)
    {
    /*  Handling The idle Case */
    case IDLE:
        if(u8StepDown==PBD_PUSHED)
        {
            enutModeState=LEFT_BLINK;
            HIF_vidSetMode(HIF_OFF_MODE);
            TIF_vidSetMode(TIF_LEFT_BLINK_MODE);
        }
        else if(u8StepUp==PBD_PUSHED)
        {
            enutModeState=RIGHT_BLINK;
            HIF_vidSetMode(HIF_OFF_MODE);
            TIF_vidSetMode(TIF_RIGHT_BLINK_MODE);
        }
        else if(u8Hazzard==PBD_PUSHED)
        {
            enutModeState=HAZZARD_BLINK;
            HIF_vidSetMode(HIF_ON_MODE);
            TIF_vidSetMode(TIF_OFF_MODE);
        }
        else
        {
            //Nothing
        }
        break;
    /*  Handling The left_blink Case */
    case LEFT_BLINK:
        if(u8StepUp==PBD_PUSHED)
        {
            enutModeState=IDLE;
            HIF_vidSetMode(HIF_OFF_MODE);
            TIF_vidSetMode(TIF_OFF_MODE);
        }
        else if(u8StepDown==PBD_PUSHED)
        {
            enutModeState=LEFT_BLINK;
            HIF_vidSetMode(HIF_OFF_MODE);
            TIF_vidSetMode(TIF_LEFT_BLINK_MODE);
        }
        else if(u8Hazzard==PBD_PUSHED)
        {
            enutModeState=HAZZARD_BLINK;
            HIF_vidSetMode(HIF_ON_MODE);
            TIF_vidSetMode(TIF_OFF_MODE);
        }
        else
        {
            //Nothing
        }
        break;
    /*  Handling The right_blink Case */
    case RIGHT_BLINK:
        if(u8StepDown==PBD_PUSHED)
        {
            enutModeState=IDLE;
            HIF_vidSetMode(HIF_OFF_MODE);
            TIF_vidSetMode(TIF_OFF_MODE);
        }
        else if(u8StepUp==PBD_PUSHED)
        {
            enutModeState=RIGHT_BLINK;
            HIF_vidSetMode(HIF_OFF_MODE);
            TIF_vidSetMode(TIF_RIGHT_BLINK_MODE);
        }
        else if(u8Hazzard==PBD_PUSHED)
        {
            enutModeState=HAZZARD_BLINK;
            HIF_vidSetMode(HIF_ON_MODE);
            TIF_vidSetMode(TIF_OFF_MODE);
        }
        else
        {
            //Nothing
        }
        break;

    /*  Handling The hazzard Case */
    case HAZZARD_BLINK:
        if( (u8StepUp==PBD_PUSHED) || (u8StepDown==PBD_PUSHED) )
        {
            enutModeState=HAZZARD_BLINK;
            HIF_vidSetMode(HIF_ON_MODE);
            TIF_vidSetMode(TIF_OFF_MODE);
        }
        else if(u8Hazzard==PBD_PRE_PUSH)
        {
            switch(enutModeStatePervious)
            {
            case IDLE:
                HIF_vidSetMode(HIF_ON_MODE);
                break;

            case LEFT_BLINK:
                HIF_vidSetMode(HIF_OFF_MODE);
                TIF_vidSetMode(TIF_LEFT_BLINK_MODE);
                enutModeStatePervious=LEFT_BLINK;
                enutModeState=HAZZARD_BLINK;
                break;

            case RIGHT_BLINK:
                HIF_vidSetMode(HIF_OFF_MODE);
                TIF_vidSetMode(TIF_RIGHT_BLINK_MODE);
                enutModeStatePervious=RIGHT_BLINK;
                enutModeState=HAZZARD_BLINK;
                break;

            case HAZZARD_BLINK:
                HIF_vidSetMode(HIF_ON_MODE);
                TIF_vidSetMode(TIF_OFF_MODE);
                enutModeState=enutModeStatePervious;
                break;
            default:
                break;

            }
        }
        else
        {
            //nothing
        }

    }


}
