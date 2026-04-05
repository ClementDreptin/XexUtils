#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Http()
{
    Describe("Http");

    It("sends a GET request", []() {
        Http::Client client;
        auto response = client.Get("jsonplaceholder.typicode.com", "/todos/1", false, 80);

        std::string expectedResponse =
            "{\n"
            "  \"userId\": 1,\n"
            "  \"id\": 1,\n"
            "  \"title\": \"delectus aut autem\",\n"
            "  \"completed\": false\n"
            "}";

        TEST_EQ(response.HasValue(), true);
        TEST_EQ(response->Status, 200);
        TEST_EQ(response->Body, expectedResponse);
    });
}
