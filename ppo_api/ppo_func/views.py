from django.shortcuts import render
from rest_framework.response import Response
from rest_framework.decorators import api_view

# @api_view(['GET'])
# def get_move(request):
#     print("GET request, received data: ", request.data)
#     return Response("111111111111111111111111111111111")

@api_view(['GET'])
def get_move(request):
    print("GET request, received data: ", request.data)
    
    # Construct the response data
    response_data = {"message": "This is the response body for the GET request"}
    
    # Return the response data regardless of the request
    return Response(response_data)

@api_view(["POST"])
def get_reward(request):
    print("POST request, received data: ", request.data)
    return Response("22222222222222222222222222222")

from django.http import JsonResponse


def get_number(request):
    number = 1  # You can change this number to any value you want
    return JsonResponse({'number': number})




