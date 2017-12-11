using UnityEngine;

public class Main : MonoBehaviour
{
    // Update is called once per frame
    void Update()
    {
        QuPlaySimtools.QuSimtools_SendTelemetry(Random.RandomRange(-180, 180), Random.RandomRange(-180, 180), Random.RandomRange(-180, 180), Random.RandomRange(-180, 180), Random.RandomRange(-180, 180), Random.RandomRange(-180, 180), Random.RandomRange(-180, 180), Random.RandomRange(-180, 180), Random.RandomRange(-180, 180));
    }
}
