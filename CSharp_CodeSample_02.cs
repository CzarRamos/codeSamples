/*
This sample code is from my Power Tower project, 
a 2-4 competitive multiplayer game student project.

This is part of the asynchronous level loading.
It has a simple fade to black and 
a loading screen for players to view the loading percent.

by Czarina Ramos
*/

    IEnumerator LoadNewScene(int sceneNumber)
    {
		//Fades to black screen
		float timeFadeEnd = 1F;
		float timePassed = 0.0F;

		imageToFade.enabled = true;
		Color colorToFade = imageToFade.color;

		while(timePassed < timeFadeEnd)
		{
			timePassed += Time.deltaTime;
			colorToFade.a += 1F * Time.deltaTime;
			imageToFade.color = colorToFade;
			yield return null;
		}

		yield return new WaitForSeconds(0.5F);
		
		//shows loading section
		sliderBar.gameObject.SetActive(true);
		loadingText.gameObject.SetActive(true);
		
		yield return new WaitForSeconds(2F);

		// Start an asynchronous operation to load the scene that was passed to the LoadNewScene coroutine.
		AsyncOperation async = SceneManager.LoadSceneAsync(sceneNumber);

        // While the asynchronous operation to load the new scene is not yet complete, continue waiting until it's done.
        //Also shows visual representation of percentage for players to view
        while (!async.isDone)
        {
            float progress = Mathf.Clamp01(async.progress);
            sliderBar.value = progress;
            loadingText.SetText(progress * 100F + "%");
            yield return null;
        }
    }