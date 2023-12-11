# forms.py

from django import forms
from .models import Post, Category

choices = Category.objects.all().values_list('name', 'name')   
choice_list = []
for item in choices:
    choice_list.append(item)
    

class BlogPostForm(forms.ModelForm):
    class Meta:
        model = Post
        fields = ("title", "author","category","body" )
        
        widgets = {
            "title": forms.TextInput(attrs={'class':'form-control'}),
            "author": forms.Select(attrs={'class':'form-control'}),
            "category": forms.Select(
                choices=[('', 'Select category')] + choice_list,
                attrs={'class': 'form-control', 'placeholder': 'Select category'}
            ),
            "body": forms.Textarea(attrs={'class':'form-control'}),
        }                     
