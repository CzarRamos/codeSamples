/*
This sample code is from my Tower of Hanoi project, 
a game where you have to stack rings on top of the other 
but not allowing bigger rings on top of the small rings.

This is the touch and drag system using Android Studio's onTouch and onDrag functions
to drag , drop, and compare the ring sizes against each other.

by Czarina Ramos
*/

public boolean onTouch(View v, MotionEvent mEvent)
    {
        //touch event code
        if(mEvent.getAction() == MotionEvent.ACTION_DOWN)
        {
            View.DragShadowBuilder sBuilder = new View.DragShadowBuilder(v);
            v.startDrag(null, sBuilder, v, 0);
            v.setVisibility(View.INVISIBLE);
            return true;
        }
        else
        {
            return false;
        }
    }

    public boolean onDrag(View layoutView, DragEvent dEvent)
    {
        int action = dEvent.getAction();

        switch(action)
        {
            case DragEvent.ACTION_DRAG_STARTED:
                break;
            case DragEvent.ACTION_DRAG_ENTERED:
                break;
            case DragEvent.ACTION_DRAG_EXITED:
                break;
            case DragEvent.ACTION_DROP:
                View v = (View)dEvent.getLocalState(); //view being held
                ViewGroup owner = (ViewGroup)v.getParent(); //previous parent layout of v
                owner.removeView(v); //removes v from parent layout
                LinearLayout container = (LinearLayout) layoutView; //the layout v is dragged towards

                int ringHeld = (int)v.getTag(); //stores tag of held ring

                if(ringCheck(ringHeld, container)) //does the ring.tag number check
                {
                    //if ring number is higher, place it at intended layout (index 0)--the top part
                    container.addView(v, 0);
                    v.setVisibility(View.VISIBLE);
                }
                else
                {
                    //if not, place at old layout, at the top--because that's the only place where they got it
                    owner.addView(v, 0);
                    v.setVisibility(View.VISIBLE);
                }
                touchEnabler();
                checkWin();
                break;
            case DragEvent.ACTION_DRAG_ENDED:
                break;
            default:
                break;
        }
        return true;
    }

    public boolean ringCheck(int ringNumHeld, LinearLayout toPlace)
    {
        if(toPlace.getChildCount() != 0)
        {
            ImageView l = (ImageView)toPlace.getChildAt(0); //checks what existing ring is in the layout

            if(ringNumHeld > (int)l.getTag())
            {
                //if ring.tag held is larger, allow to stack it
                return true;
            }
            else if(ringNumHeld < (int)l.getTag())
            {
                //if ring.tag is smaller, do not stack it; return it
                return false;
            }
        }
        //default; if the number of rings in the layout is 0, don't bother checking--just let it stack
        return true;
    }

    public void checkWin()
    {
        if(layoutBlue3.getChildCount() == ringNum)
        {
            for(int i = 0; i < layoutBlue3.getChildCount(); i++)
            {
                layoutBlue3.getChildAt(i).setEnabled(false);
                Toast.makeText(this, "YOU WON!", Toast.LENGTH_LONG).show();
            }
        }
    }