// Copyright (c) 2011-2016, NVIDIA CORPORATION. All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#include <dp/sg/renderer/rix/gl/inc/ResourceIndexSet.h>
#include <dp/sg/core/IndexSet.h>
#include <dp/sg/core/Buffer.h>

namespace dp
{
  namespace sg
  {
    namespace renderer
    {
      namespace rix
      {
        namespace gl
        {

          ResourceIndexSetSharedPtr ResourceIndexSet::get( const dp::sg::core::IndexSetSharedPtr &indexSet, const ResourceManagerSharedPtr& resourceManager )
          {
            assert( indexSet );
            assert( resourceManager );

            ResourceIndexSetSharedPtr resourceIndexSet = resourceManager->getResource<ResourceIndexSet>( reinterpret_cast<size_t>(indexSet.operator->()) );   // Big Hack !!
            if ( !resourceIndexSet )
            {
              resourceIndexSet = std::shared_ptr<ResourceIndexSet>( new ResourceIndexSet( indexSet, resourceManager ) );
              resourceIndexSet->m_indicesHandle = resourceManager->getRenderer()->indicesCreate();
              resourceIndexSet->update();
            }

            return resourceIndexSet;
          }

          ResourceIndexSet::ResourceIndexSet( const dp::sg::core::IndexSetSharedPtr &indexSet, const ResourceManagerSharedPtr& resourceManager )
            : ResourceManager::Resource( reinterpret_cast<size_t>( indexSet.operator->() ), resourceManager )   // Big Hack !!
            , m_indexSet( indexSet )
          {
            resourceManager->subscribe( this );
          }

          ResourceIndexSet::~ResourceIndexSet()
          {
            m_resourceManager->unsubscribe( this );
          }

          dp::sg::core::HandledObjectSharedPtr ResourceIndexSet::getHandledObject() const
          {
            return std::static_pointer_cast<dp::sg::core::HandledObject>(m_indexSet);
          }

          void ResourceIndexSet::update()
          {
            /** copy over indices **/
            unsigned int restart = ~0;

            unsigned int numIndices = m_indexSet->getNumberOfIndices();

            m_resourceBuffer = ResourceBuffer::get( m_indexSet->getBuffer(), m_resourceManager );
            // TODO offset

            m_resourceManager->getRenderer()->indicesSetData( m_indicesHandle
              , m_indexSet->getIndexDataType()
              , m_resourceBuffer->m_bufferHandle
              , 0, numIndices
              );
          }

        } // namespace gl
      } // namespace rix
    } // namespace renderer
  } // namespace sg
} // namespace dp

